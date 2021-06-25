<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * refcounttree.c
 *
 * Copyright (C) 2009 Oracle.  All rights reserved.
 */

#समावेश <linux/sort.h>
#समावेश <cluster/masklog.h>
#समावेश "ocfs2.h"
#समावेश "inode.h"
#समावेश "alloc.h"
#समावेश "suballoc.h"
#समावेश "journal.h"
#समावेश "uptodate.h"
#समावेश "super.h"
#समावेश "buffer_head_io.h"
#समावेश "blockcheck.h"
#समावेश "refcounttree.h"
#समावेश "sysfile.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "aops.h"
#समावेश "xattr.h"
#समावेश "namei.h"
#समावेश "ocfs2_trace.h"
#समावेश "file.h"

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/swap.h>
#समावेश <linux/security.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/quotaops.h>
#समावेश <linux/namei.h>
#समावेश <linux/mount.h>
#समावेश <linux/posix_acl.h>

काष्ठा ocfs2_cow_context अणु
	काष्ठा inode *inode;
	u32 cow_start;
	u32 cow_len;
	काष्ठा ocfs2_extent_tree data_et;
	काष्ठा ocfs2_refcount_tree *ref_tree;
	काष्ठा buffer_head *ref_root_bh;
	काष्ठा ocfs2_alloc_context *meta_ac;
	काष्ठा ocfs2_alloc_context *data_ac;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	व्योम *cow_object;
	काष्ठा ocfs2_post_refcount *post_refcount;
	पूर्णांक extra_credits;
	पूर्णांक (*get_clusters)(काष्ठा ocfs2_cow_context *context,
			    u32 v_cluster, u32 *p_cluster,
			    u32 *num_clusters,
			    अचिन्हित पूर्णांक *extent_flags);
	पूर्णांक (*cow_duplicate_clusters)(handle_t *handle,
				      काष्ठा inode *inode,
				      u32 cpos, u32 old_cluster,
				      u32 new_cluster, u32 new_len);
पूर्ण;

अटल अंतरभूत काष्ठा ocfs2_refcount_tree *
cache_info_to_refcount(काष्ठा ocfs2_caching_info *ci)
अणु
	वापस container_of(ci, काष्ठा ocfs2_refcount_tree, rf_ci);
पूर्ण

अटल पूर्णांक ocfs2_validate_refcount_block(काष्ठा super_block *sb,
					 काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_refcount_block *rb =
		(काष्ठा ocfs2_refcount_block *)bh->b_data;

	trace_ocfs2_validate_refcount_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &rb->rf_check);
	अगर (rc) अणु
		mlog(ML_ERROR, "Checksum failed for refcount block %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस rc;
	पूर्ण


	अगर (!OCFS2_IS_VALID_REFCOUNT_BLOCK(rb)) अणु
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has bad signature %.*s\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
				 rb->rf_signature);
		जाओ out;
	पूर्ण

	अगर (le64_to_cpu(rb->rf_blkno) != bh->b_blocknr) अणु
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has an invalid rf_blkno of %llu\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(rb->rf_blkno));
		जाओ out;
	पूर्ण

	अगर (le32_to_cpu(rb->rf_fs_generation) != OCFS2_SB(sb)->fs_generation) अणु
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has an invalid rf_fs_generation of #%u\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 le32_to_cpu(rb->rf_fs_generation));
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_refcount_block(काष्ठा ocfs2_caching_info *ci,
				     u64 rb_blkno,
				     काष्ठा buffer_head **bh)
अणु
	पूर्णांक rc;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_block(ci, rb_blkno, &पंचांगp,
			      ocfs2_validate_refcount_block);

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!rc && !*bh)
		*bh = पंचांगp;

	वापस rc;
पूर्ण

अटल u64 ocfs2_refcount_cache_owner(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	वापस rf->rf_blkno;
पूर्ण

अटल काष्ठा super_block *
ocfs2_refcount_cache_get_super(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	वापस rf->rf_sb;
पूर्ण

अटल व्योम ocfs2_refcount_cache_lock(काष्ठा ocfs2_caching_info *ci)
__acquires(&rf->rf_lock)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	spin_lock(&rf->rf_lock);
पूर्ण

अटल व्योम ocfs2_refcount_cache_unlock(काष्ठा ocfs2_caching_info *ci)
__releases(&rf->rf_lock)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	spin_unlock(&rf->rf_lock);
पूर्ण

अटल व्योम ocfs2_refcount_cache_io_lock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	mutex_lock(&rf->rf_io_mutex);
पूर्ण

अटल व्योम ocfs2_refcount_cache_io_unlock(काष्ठा ocfs2_caching_info *ci)
अणु
	काष्ठा ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	mutex_unlock(&rf->rf_io_mutex);
पूर्ण

अटल स्थिर काष्ठा ocfs2_caching_operations ocfs2_refcount_caching_ops = अणु
	.co_owner		= ocfs2_refcount_cache_owner,
	.co_get_super		= ocfs2_refcount_cache_get_super,
	.co_cache_lock		= ocfs2_refcount_cache_lock,
	.co_cache_unlock	= ocfs2_refcount_cache_unlock,
	.co_io_lock		= ocfs2_refcount_cache_io_lock,
	.co_io_unlock		= ocfs2_refcount_cache_io_unlock,
पूर्ण;

अटल काष्ठा ocfs2_refcount_tree *
ocfs2_find_refcount_tree(काष्ठा ocfs2_super *osb, u64 blkno)
अणु
	काष्ठा rb_node *n = osb->osb_rf_lock_tree.rb_node;
	काष्ठा ocfs2_refcount_tree *tree = शून्य;

	जबतक (n) अणु
		tree = rb_entry(n, काष्ठा ocfs2_refcount_tree, rf_node);

		अगर (blkno < tree->rf_blkno)
			n = n->rb_left;
		अन्यथा अगर (blkno > tree->rf_blkno)
			n = n->rb_right;
		अन्यथा
			वापस tree;
	पूर्ण

	वापस शून्य;
पूर्ण

/* osb_lock is alपढ़ोy locked. */
अटल व्योम ocfs2_insert_refcount_tree(काष्ठा ocfs2_super *osb,
				       काष्ठा ocfs2_refcount_tree *new)
अणु
	u64 rf_blkno = new->rf_blkno;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_node **p = &osb->osb_rf_lock_tree.rb_node;
	काष्ठा ocfs2_refcount_tree *पंचांगp;

	जबतक (*p) अणु
		parent = *p;

		पंचांगp = rb_entry(parent, काष्ठा ocfs2_refcount_tree,
			       rf_node);

		अगर (rf_blkno < पंचांगp->rf_blkno)
			p = &(*p)->rb_left;
		अन्यथा अगर (rf_blkno > पंचांगp->rf_blkno)
			p = &(*p)->rb_right;
		अन्यथा अणु
			/* This should never happen! */
			mlog(ML_ERROR, "Duplicate refcount block %llu found!\n",
			     (अचिन्हित दीर्घ दीर्घ)rf_blkno);
			BUG();
		पूर्ण
	पूर्ण

	rb_link_node(&new->rf_node, parent, p);
	rb_insert_color(&new->rf_node, &osb->osb_rf_lock_tree);
पूर्ण

अटल व्योम ocfs2_मुक्त_refcount_tree(काष्ठा ocfs2_refcount_tree *tree)
अणु
	ocfs2_metadata_cache_निकास(&tree->rf_ci);
	ocfs2_simple_drop_lockres(OCFS2_SB(tree->rf_sb), &tree->rf_lockres);
	ocfs2_lock_res_मुक्त(&tree->rf_lockres);
	kमुक्त(tree);
पूर्ण

अटल अंतरभूत व्योम
ocfs2_erase_refcount_tree_from_list_no_lock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_refcount_tree *tree)
अणु
	rb_erase(&tree->rf_node, &osb->osb_rf_lock_tree);
	अगर (osb->osb_ref_tree_lru && osb->osb_ref_tree_lru == tree)
		osb->osb_ref_tree_lru = शून्य;
पूर्ण

अटल व्योम ocfs2_erase_refcount_tree_from_list(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_refcount_tree *tree)
अणु
	spin_lock(&osb->osb_lock);
	ocfs2_erase_refcount_tree_from_list_no_lock(osb, tree);
	spin_unlock(&osb->osb_lock);
पूर्ण

अटल व्योम ocfs2_kref_हटाओ_refcount_tree(काष्ठा kref *kref)
अणु
	काष्ठा ocfs2_refcount_tree *tree =
		container_of(kref, काष्ठा ocfs2_refcount_tree, rf_अ_लोnt);

	ocfs2_मुक्त_refcount_tree(tree);
पूर्ण

अटल अंतरभूत व्योम
ocfs2_refcount_tree_get(काष्ठा ocfs2_refcount_tree *tree)
अणु
	kref_get(&tree->rf_अ_लोnt);
पूर्ण

अटल अंतरभूत व्योम
ocfs2_refcount_tree_put(काष्ठा ocfs2_refcount_tree *tree)
अणु
	kref_put(&tree->rf_अ_लोnt, ocfs2_kref_हटाओ_refcount_tree);
पूर्ण

अटल अंतरभूत व्योम ocfs2_init_refcount_tree_ci(काष्ठा ocfs2_refcount_tree *new,
					       काष्ठा super_block *sb)
अणु
	ocfs2_metadata_cache_init(&new->rf_ci, &ocfs2_refcount_caching_ops);
	mutex_init(&new->rf_io_mutex);
	new->rf_sb = sb;
	spin_lock_init(&new->rf_lock);
पूर्ण

अटल अंतरभूत व्योम ocfs2_init_refcount_tree_lock(काष्ठा ocfs2_super *osb,
					काष्ठा ocfs2_refcount_tree *new,
					u64 rf_blkno, u32 generation)
अणु
	init_rwsem(&new->rf_sem);
	ocfs2_refcount_lock_res_init(&new->rf_lockres, osb,
				     rf_blkno, generation);
पूर्ण

अटल काष्ठा ocfs2_refcount_tree*
ocfs2_allocate_refcount_tree(काष्ठा ocfs2_super *osb, u64 rf_blkno)
अणु
	काष्ठा ocfs2_refcount_tree *new;

	new = kzalloc(माप(काष्ठा ocfs2_refcount_tree), GFP_NOFS);
	अगर (!new)
		वापस शून्य;

	new->rf_blkno = rf_blkno;
	kref_init(&new->rf_अ_लोnt);
	ocfs2_init_refcount_tree_ci(new, osb->sb);

	वापस new;
पूर्ण

अटल पूर्णांक ocfs2_get_refcount_tree(काष्ठा ocfs2_super *osb, u64 rf_blkno,
				   काष्ठा ocfs2_refcount_tree **ret_tree)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_refcount_tree *tree, *new = शून्य;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_block *ref_rb;

	spin_lock(&osb->osb_lock);
	अगर (osb->osb_ref_tree_lru &&
	    osb->osb_ref_tree_lru->rf_blkno == rf_blkno)
		tree = osb->osb_ref_tree_lru;
	अन्यथा
		tree = ocfs2_find_refcount_tree(osb, rf_blkno);
	अगर (tree)
		जाओ out;

	spin_unlock(&osb->osb_lock);

	new = ocfs2_allocate_refcount_tree(osb, rf_blkno);
	अगर (!new) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण
	/*
	 * We need the generation to create the refcount tree lock and since
	 * it isn't changed during the tree modअगरication, we are safe here to
	 * पढ़ो without protection.
	 * We also have to purge the cache after we create the lock since the
	 * refcount block may have the stale data. It can only be trusted when
	 * we hold the refcount lock.
	 */
	ret = ocfs2_पढ़ो_refcount_block(&new->rf_ci, rf_blkno, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		ocfs2_metadata_cache_निकास(&new->rf_ci);
		kमुक्त(new);
		वापस ret;
	पूर्ण

	ref_rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	new->rf_generation = le32_to_cpu(ref_rb->rf_generation);
	ocfs2_init_refcount_tree_lock(osb, new, rf_blkno,
				      new->rf_generation);
	ocfs2_metadata_cache_purge(&new->rf_ci);

	spin_lock(&osb->osb_lock);
	tree = ocfs2_find_refcount_tree(osb, rf_blkno);
	अगर (tree)
		जाओ out;

	ocfs2_insert_refcount_tree(osb, new);

	tree = new;
	new = शून्य;

out:
	*ret_tree = tree;

	osb->osb_ref_tree_lru = tree;

	spin_unlock(&osb->osb_lock);

	अगर (new)
		ocfs2_मुक्त_refcount_tree(new);

	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_get_refcount_block(काष्ठा inode *inode, u64 *ref_blkno)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;

	ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	*ref_blkno = le64_to_cpu(di->i_refcount_loc);
	brअन्यथा(di_bh);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_lock_refcount_tree(काष्ठा ocfs2_super *osb,
				      काष्ठा ocfs2_refcount_tree *tree, पूर्णांक rw)
अणु
	पूर्णांक ret;

	ret = ocfs2_refcount_lock(tree, rw);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (rw)
		करोwn_ग_लिखो(&tree->rf_sem);
	अन्यथा
		करोwn_पढ़ो(&tree->rf_sem);

out:
	वापस ret;
पूर्ण

/*
 * Lock the refcount tree poपूर्णांकed by ref_blkno and वापस the tree.
 * In most हाल, we lock the tree and पढ़ो the refcount block.
 * So पढ़ो it here अगर the caller really needs it.
 *
 * If the tree has been re-created by other node, it will मुक्त the
 * old one and re-create it.
 */
पूर्णांक ocfs2_lock_refcount_tree(काष्ठा ocfs2_super *osb,
			     u64 ref_blkno, पूर्णांक rw,
			     काष्ठा ocfs2_refcount_tree **ret_tree,
			     काष्ठा buffer_head **ref_bh)
अणु
	पूर्णांक ret, delete_tree = 0;
	काष्ठा ocfs2_refcount_tree *tree = शून्य;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_block *rb;

again:
	ret = ocfs2_get_refcount_tree(osb, ref_blkno, &tree);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ocfs2_refcount_tree_get(tree);

	ret = __ocfs2_lock_refcount_tree(osb, tree, rw);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		ocfs2_refcount_tree_put(tree);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_refcount_block(&tree->rf_ci, tree->rf_blkno,
					&ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		ocfs2_unlock_refcount_tree(osb, tree, rw);
		जाओ out;
	पूर्ण

	rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	/*
	 * If the refcount block has been मुक्तd and re-created, we may need
	 * to recreate the refcount tree also.
	 *
	 * Here we just हटाओ the tree from the rb-tree, and the last
	 * kref holder will unlock and delete this refcount_tree.
	 * Then we जाओ "again" and ocfs2_get_refcount_tree will create
	 * the new refcount tree क्रम us.
	 */
	अगर (tree->rf_generation != le32_to_cpu(rb->rf_generation)) अणु
		अगर (!tree->rf_हटाओd) अणु
			ocfs2_erase_refcount_tree_from_list(osb, tree);
			tree->rf_हटाओd = 1;
			delete_tree = 1;
		पूर्ण

		ocfs2_unlock_refcount_tree(osb, tree, rw);
		/*
		 * We get an extra reference when we create the refcount
		 * tree, so another put will destroy it.
		 */
		अगर (delete_tree)
			ocfs2_refcount_tree_put(tree);
		brअन्यथा(ref_root_bh);
		ref_root_bh = शून्य;
		जाओ again;
	पूर्ण

	*ret_tree = tree;
	अगर (ref_bh) अणु
		*ref_bh = ref_root_bh;
		ref_root_bh = शून्य;
	पूर्ण
out:
	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

व्योम ocfs2_unlock_refcount_tree(काष्ठा ocfs2_super *osb,
				काष्ठा ocfs2_refcount_tree *tree, पूर्णांक rw)
अणु
	अगर (rw)
		up_ग_लिखो(&tree->rf_sem);
	अन्यथा
		up_पढ़ो(&tree->rf_sem);

	ocfs2_refcount_unlock(tree, rw);
	ocfs2_refcount_tree_put(tree);
पूर्ण

व्योम ocfs2_purge_refcount_trees(काष्ठा ocfs2_super *osb)
अणु
	काष्ठा rb_node *node;
	काष्ठा ocfs2_refcount_tree *tree;
	काष्ठा rb_root *root = &osb->osb_rf_lock_tree;

	जबतक ((node = rb_last(root)) != शून्य) अणु
		tree = rb_entry(node, काष्ठा ocfs2_refcount_tree, rf_node);

		trace_ocfs2_purge_refcount_trees(
				(अचिन्हित दीर्घ दीर्घ) tree->rf_blkno);

		rb_erase(&tree->rf_node, root);
		ocfs2_मुक्त_refcount_tree(tree);
	पूर्ण
पूर्ण

/*
 * Create a refcount tree क्रम an inode.
 * We take क्रम granted that the inode is alपढ़ोy locked.
 */
अटल पूर्णांक ocfs2_create_refcount_tree(काष्ठा inode *inode,
				      काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_refcount_block *rb;
	काष्ठा ocfs2_refcount_tree *new_tree = शून्य, *tree = शून्य;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, first_blkno;

	BUG_ON(ocfs2_is_refcount_inode(inode));

	trace_ocfs2_create_refcount_tree(
		(अचिन्हित दीर्घ दीर्घ)oi->ip_blkno);

	ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_REFCOUNT_TREE_CREATE_CREDITS);
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

	ret = ocfs2_claim_metadata(handle, meta_ac, 1, &suballoc_loc,
				   &suballoc_bit_start, &num_got,
				   &first_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	new_tree = ocfs2_allocate_refcount_tree(osb, first_blkno);
	अगर (!new_tree) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	new_bh = sb_getblk(inode->i_sb, first_blkno);
	अगर (!new_bh) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(&new_tree->rf_ci, new_bh);

	ret = ocfs2_journal_access_rb(handle, &new_tree->rf_ci, new_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/* Initialize ocfs2_refcount_block. */
	rb = (काष्ठा ocfs2_refcount_block *)new_bh->b_data;
	स_रखो(rb, 0, inode->i_sb->s_blocksize);
	म_नकल((व्योम *)rb, OCFS2_REFCOUNT_BLOCK_SIGNATURE);
	rb->rf_suballoc_slot = cpu_to_le16(meta_ac->ac_alloc_slot);
	rb->rf_suballoc_loc = cpu_to_le64(suballoc_loc);
	rb->rf_suballoc_bit = cpu_to_le16(suballoc_bit_start);
	rb->rf_fs_generation = cpu_to_le32(osb->fs_generation);
	rb->rf_blkno = cpu_to_le64(first_blkno);
	rb->rf_count = cpu_to_le32(1);
	rb->rf_records.rl_count =
			cpu_to_le16(ocfs2_refcount_recs_per_rb(osb->sb));
	spin_lock(&osb->osb_lock);
	rb->rf_generation = osb->s_next_generation++;
	spin_unlock(&osb->osb_lock);

	ocfs2_journal_dirty(handle, new_bh);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_HAS_REFCOUNT_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	di->i_refcount_loc = cpu_to_le64(first_blkno);
	spin_unlock(&oi->ip_lock);

	trace_ocfs2_create_refcount_tree_blkno((अचिन्हित दीर्घ दीर्घ)first_blkno);

	ocfs2_journal_dirty(handle, di_bh);

	/*
	 * We have to init the tree lock here since it will use
	 * the generation number to create it.
	 */
	new_tree->rf_generation = le32_to_cpu(rb->rf_generation);
	ocfs2_init_refcount_tree_lock(osb, new_tree, first_blkno,
				      new_tree->rf_generation);

	spin_lock(&osb->osb_lock);
	tree = ocfs2_find_refcount_tree(osb, first_blkno);

	/*
	 * We've just created a new refcount tree in this block.  If
	 * we found a refcount tree on the ocfs2_super, it must be
	 * one we just deleted.  We मुक्त the old tree beक्रमe
	 * inserting the new tree.
	 */
	BUG_ON(tree && tree->rf_generation == new_tree->rf_generation);
	अगर (tree)
		ocfs2_erase_refcount_tree_from_list_no_lock(osb, tree);
	ocfs2_insert_refcount_tree(osb, new_tree);
	spin_unlock(&osb->osb_lock);
	new_tree = शून्य;
	अगर (tree)
		ocfs2_refcount_tree_put(tree);

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	अगर (new_tree) अणु
		ocfs2_metadata_cache_निकास(&new_tree->rf_ci);
		kमुक्त(new_tree);
	पूर्ण

	brअन्यथा(new_bh);
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_set_refcount_tree(काष्ठा inode *inode,
				   काष्ठा buffer_head *di_bh,
				   u64 refcount_loc)
अणु
	पूर्णांक ret;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_block *rb;
	काष्ठा ocfs2_refcount_tree *ref_tree;

	BUG_ON(ocfs2_is_refcount_inode(inode));

	ret = ocfs2_lock_refcount_tree(osb, refcount_loc, 1,
				       &ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_REFCOUNT_TREE_SET_CREDITS);
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

	ret = ocfs2_journal_access_rb(handle, &ref_tree->rf_ci, ref_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	le32_add_cpu(&rb->rf_count, 1);

	ocfs2_journal_dirty(handle, ref_root_bh);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_HAS_REFCOUNT_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	di->i_refcount_loc = cpu_to_le64(refcount_loc);
	spin_unlock(&oi->ip_lock);
	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brअन्यथा(ref_root_bh);

	वापस ret;
पूर्ण

पूर्णांक ocfs2_हटाओ_refcount_tree(काष्ठा inode *inode, काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret, delete_tree = 0;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_refcount_block *rb;
	काष्ठा inode *alloc_inode = शून्य;
	काष्ठा buffer_head *alloc_bh = शून्य;
	काष्ठा buffer_head *blk_bh = शून्य;
	काष्ठा ocfs2_refcount_tree *ref_tree;
	पूर्णांक credits = OCFS2_REFCOUNT_TREE_REMOVE_CREDITS;
	u64 blk = 0, bg_blkno = 0, ref_blkno = le64_to_cpu(di->i_refcount_loc);
	u16 bit = 0;

	अगर (!ocfs2_is_refcount_inode(inode))
		वापस 0;

	BUG_ON(!ref_blkno);
	ret = ocfs2_lock_refcount_tree(osb, ref_blkno, 1, &ref_tree, &blk_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	rb = (काष्ठा ocfs2_refcount_block *)blk_bh->b_data;

	/*
	 * If we are the last user, we need to मुक्त the block.
	 * So lock the allocator ahead.
	 */
	अगर (le32_to_cpu(rb->rf_count) == 1) अणु
		blk = le64_to_cpu(rb->rf_blkno);
		bit = le16_to_cpu(rb->rf_suballoc_bit);
		अगर (rb->rf_suballoc_loc)
			bg_blkno = le64_to_cpu(rb->rf_suballoc_loc);
		अन्यथा
			bg_blkno = ocfs2_which_suballoc_group(blk, bit);

		alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
					EXTENT_ALLOC_SYSTEM_INODE,
					le16_to_cpu(rb->rf_suballoc_slot));
		अगर (!alloc_inode) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		inode_lock(alloc_inode);

		ret = ocfs2_inode_lock(alloc_inode, &alloc_bh, 1);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_mutex;
		पूर्ण

		credits += OCFS2_SUBALLOC_FREE;
	पूर्ण

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, &ref_tree->rf_ci, blk_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~OCFS2_HAS_REFCOUNT_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	di->i_refcount_loc = 0;
	spin_unlock(&oi->ip_lock);
	ocfs2_journal_dirty(handle, di_bh);

	le32_add_cpu(&rb->rf_count , -1);
	ocfs2_journal_dirty(handle, blk_bh);

	अगर (!rb->rf_count) अणु
		delete_tree = 1;
		ocfs2_erase_refcount_tree_from_list(osb, ref_tree);
		ret = ocfs2_मुक्त_suballoc_bits(handle, alloc_inode,
					       alloc_bh, bit, bg_blkno, 1);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out_commit:
	ocfs2_commit_trans(osb, handle);
out_unlock:
	अगर (alloc_inode) अणु
		ocfs2_inode_unlock(alloc_inode, 1);
		brअन्यथा(alloc_bh);
	पूर्ण
out_mutex:
	अगर (alloc_inode) अणु
		inode_unlock(alloc_inode);
		iput(alloc_inode);
	पूर्ण
out:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	अगर (delete_tree)
		ocfs2_refcount_tree_put(ref_tree);
	brअन्यथा(blk_bh);

	वापस ret;
पूर्ण

अटल व्योम ocfs2_find_refcount_rec_in_rl(काष्ठा ocfs2_caching_info *ci,
					  काष्ठा buffer_head *ref_leaf_bh,
					  u64 cpos, अचिन्हित पूर्णांक len,
					  काष्ठा ocfs2_refcount_rec *ret_rec,
					  पूर्णांक *index)
अणु
	पूर्णांक i = 0;
	काष्ठा ocfs2_refcount_block *rb =
		(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_rec *rec = शून्य;

	क्रम (; i < le16_to_cpu(rb->rf_records.rl_used); i++) अणु
		rec = &rb->rf_records.rl_recs[i];

		अगर (le64_to_cpu(rec->r_cpos) +
		    le32_to_cpu(rec->r_clusters) <= cpos)
			जारी;
		अन्यथा अगर (le64_to_cpu(rec->r_cpos) > cpos)
			अवरोध;

		/* ok, cpos fail in this rec. Just वापस. */
		अगर (ret_rec)
			*ret_rec = *rec;
		जाओ out;
	पूर्ण

	अगर (ret_rec) अणु
		/* We meet with a hole here, so fake the rec. */
		ret_rec->r_cpos = cpu_to_le64(cpos);
		ret_rec->r_refcount = 0;
		अगर (i < le16_to_cpu(rb->rf_records.rl_used) &&
		    le64_to_cpu(rec->r_cpos) < cpos + len)
			ret_rec->r_clusters =
				cpu_to_le32(le64_to_cpu(rec->r_cpos) - cpos);
		अन्यथा
			ret_rec->r_clusters = cpu_to_le32(len);
	पूर्ण

out:
	*index = i;
पूर्ण

/*
 * Try to हटाओ refcount tree. The mechanism is:
 * 1) Check whether i_clusters == 0, अगर no, निकास.
 * 2) check whether we have i_xattr_loc in dinode. अगर yes, निकास.
 * 3) Check whether we have अंतरभूत xattr stored outside, अगर yes, निकास.
 * 4) Remove the tree.
 */
पूर्णांक ocfs2_try_हटाओ_refcount_tree(काष्ठा inode *inode,
				   काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	करोwn_ग_लिखो(&oi->ip_xattr_sem);
	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	अगर (oi->ip_clusters)
		जाओ out;

	अगर ((oi->ip_dyn_features & OCFS2_HAS_XATTR_FL) && di->i_xattr_loc)
		जाओ out;

	अगर (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL &&
	    ocfs2_has_अंतरभूत_xattr_value_outside(inode, di))
		जाओ out;

	ret = ocfs2_हटाओ_refcount_tree(inode, di_bh);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
out:
	up_ग_लिखो(&oi->ip_alloc_sem);
	up_ग_लिखो(&oi->ip_xattr_sem);
	वापस 0;
पूर्ण

/*
 * Find the end range क्रम a leaf refcount block indicated by
 * el->l_recs[index].e_blkno.
 */
अटल पूर्णांक ocfs2_get_refcount_cpos_end(काष्ठा ocfs2_caching_info *ci,
				       काष्ठा buffer_head *ref_root_bh,
				       काष्ठा ocfs2_extent_block *eb,
				       काष्ठा ocfs2_extent_list *el,
				       पूर्णांक index,  u32 *cpos_end)
अणु
	पूर्णांक ret, i, subtree_root;
	u32 cpos;
	u64 blkno;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा ocfs2_path *left_path = शून्य, *right_path = शून्य;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_extent_list *पंचांगp_el;

	अगर (index < le16_to_cpu(el->l_next_मुक्त_rec) - 1) अणु
		/*
		 * We have a extent rec after index, so just use the e_cpos
		 * of the next extent rec.
		 */
		*cpos_end = le32_to_cpu(el->l_recs[index+1].e_cpos);
		वापस 0;
	पूर्ण

	अगर (!eb || !eb->h_next_leaf_blk) अणु
		/*
		 * We are the last extent rec, so any high cpos should
		 * be stored in this leaf refcount block.
		 */
		*cpos_end = अच_पूर्णांक_उच्च;
		वापस 0;
	पूर्ण

	/*
	 * If the extent block isn't the last one, we have to find
	 * the subtree root between this extent block and the next
	 * leaf extent block and get the corresponding e_cpos from
	 * the subroot. Otherwise we may corrupt the b-tree.
	 */
	ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);

	left_path = ocfs2_new_path_from_et(&et);
	अगर (!left_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	cpos = le32_to_cpu(eb->h_list.l_recs[index].e_cpos);
	ret = ocfs2_find_path(ci, left_path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	right_path = ocfs2_new_path_from_path(left_path);
	अगर (!right_path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_cpos_क्रम_right_leaf(sb, left_path, &cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(ci, right_path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	subtree_root = ocfs2_find_subtree_root(&et, left_path,
					       right_path);

	पंचांगp_el = left_path->p_node[subtree_root].el;
	blkno = left_path->p_node[subtree_root+1].bh->b_blocknr;
	क्रम (i = 0; i < le16_to_cpu(पंचांगp_el->l_next_मुक्त_rec); i++) अणु
		अगर (le64_to_cpu(पंचांगp_el->l_recs[i].e_blkno) == blkno) अणु
			*cpos_end = le32_to_cpu(पंचांगp_el->l_recs[i+1].e_cpos);
			अवरोध;
		पूर्ण
	पूर्ण

	BUG_ON(i == le16_to_cpu(पंचांगp_el->l_next_मुक्त_rec));

out:
	ocfs2_मुक्त_path(left_path);
	ocfs2_मुक्त_path(right_path);
	वापस ret;
पूर्ण

/*
 * Given a cpos and len, try to find the refcount record which contains cpos.
 * 1. If cpos can be found in one refcount record, वापस the record.
 * 2. If cpos can't be found, वापस a fake record which start from cpos
 *    and end at a small value between cpos+len and start of the next record.
 *    This fake record has r_refcount = 0.
 */
अटल पूर्णांक ocfs2_get_refcount_rec(काष्ठा ocfs2_caching_info *ci,
				  काष्ठा buffer_head *ref_root_bh,
				  u64 cpos, अचिन्हित पूर्णांक len,
				  काष्ठा ocfs2_refcount_rec *ret_rec,
				  पूर्णांक *index,
				  काष्ठा buffer_head **ret_bh)
अणु
	पूर्णांक ret = 0, i, found;
	u32 low_cpos, cpos_end;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा ocfs2_extent_rec *rec = शून्य;
	काष्ठा ocfs2_extent_block *eb = शून्य;
	काष्ठा buffer_head *eb_bh = शून्य, *ref_leaf_bh = शून्य;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;

	अगर (!(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)) अणु
		ocfs2_find_refcount_rec_in_rl(ci, ref_root_bh, cpos, len,
					      ret_rec, index);
		*ret_bh = ref_root_bh;
		get_bh(ref_root_bh);
		वापस 0;
	पूर्ण

	el = &rb->rf_list;
	low_cpos = cpos & OCFS2_32BIT_POS_MASK;

	अगर (el->l_tree_depth) अणु
		ret = ocfs2_find_leaf(ci, el, low_cpos, &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ret = ocfs2_error(sb,
					  "refcount tree %llu has non zero tree depth in leaf btree tree block %llu\n",
					  (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
					  (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			जाओ out;
		पूर्ण
	पूर्ण

	found = 0;
	क्रम (i = le16_to_cpu(el->l_next_मुक्त_rec) - 1; i >= 0; i--) अणु
		rec = &el->l_recs[i];

		अगर (le32_to_cpu(rec->e_cpos) <= low_cpos) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		ret = ocfs2_get_refcount_cpos_end(ci, ref_root_bh,
						  eb, el, i, &cpos_end);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (cpos_end < low_cpos + len)
			len = cpos_end - low_cpos;
	पूर्ण

	ret = ocfs2_पढ़ो_refcount_block(ci, le64_to_cpu(rec->e_blkno),
					&ref_leaf_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_find_refcount_rec_in_rl(ci, ref_leaf_bh, cpos, len,
				      ret_rec, index);
	*ret_bh = ref_leaf_bh;
out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

क्रमागत ocfs2_ref_rec_contig अणु
	REF_CONTIG_NONE = 0,
	REF_CONTIG_LEFT,
	REF_CONTIG_RIGHT,
	REF_CONTIG_LEFTRIGHT,
पूर्ण;

अटल क्रमागत ocfs2_ref_rec_contig
	ocfs2_refcount_rec_adjacent(काष्ठा ocfs2_refcount_block *rb,
				    पूर्णांक index)
अणु
	अगर ((rb->rf_records.rl_recs[index].r_refcount ==
	    rb->rf_records.rl_recs[index + 1].r_refcount) &&
	    (le64_to_cpu(rb->rf_records.rl_recs[index].r_cpos) +
	    le32_to_cpu(rb->rf_records.rl_recs[index].r_clusters) ==
	    le64_to_cpu(rb->rf_records.rl_recs[index + 1].r_cpos)))
		वापस REF_CONTIG_RIGHT;

	वापस REF_CONTIG_NONE;
पूर्ण

अटल क्रमागत ocfs2_ref_rec_contig
	ocfs2_refcount_rec_contig(काष्ठा ocfs2_refcount_block *rb,
				  पूर्णांक index)
अणु
	क्रमागत ocfs2_ref_rec_contig ret = REF_CONTIG_NONE;

	अगर (index < le16_to_cpu(rb->rf_records.rl_used) - 1)
		ret = ocfs2_refcount_rec_adjacent(rb, index);

	अगर (index > 0) अणु
		क्रमागत ocfs2_ref_rec_contig पंचांगp;

		पंचांगp = ocfs2_refcount_rec_adjacent(rb, index - 1);

		अगर (पंचांगp == REF_CONTIG_RIGHT) अणु
			अगर (ret == REF_CONTIG_RIGHT)
				ret = REF_CONTIG_LEFTRIGHT;
			अन्यथा
				ret = REF_CONTIG_LEFT;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ocfs2_rotate_refcount_rec_left(काष्ठा ocfs2_refcount_block *rb,
					   पूर्णांक index)
अणु
	BUG_ON(rb->rf_records.rl_recs[index].r_refcount !=
	       rb->rf_records.rl_recs[index+1].r_refcount);

	le32_add_cpu(&rb->rf_records.rl_recs[index].r_clusters,
		     le32_to_cpu(rb->rf_records.rl_recs[index+1].r_clusters));

	अगर (index < le16_to_cpu(rb->rf_records.rl_used) - 2)
		स_हटाओ(&rb->rf_records.rl_recs[index + 1],
			&rb->rf_records.rl_recs[index + 2],
			माप(काष्ठा ocfs2_refcount_rec) *
			(le16_to_cpu(rb->rf_records.rl_used) - index - 2));

	स_रखो(&rb->rf_records.rl_recs[le16_to_cpu(rb->rf_records.rl_used) - 1],
	       0, माप(काष्ठा ocfs2_refcount_rec));
	le16_add_cpu(&rb->rf_records.rl_used, -1);
पूर्ण

/*
 * Merge the refcount rec अगर we are contiguous with the adjacent recs.
 */
अटल व्योम ocfs2_refcount_rec_merge(काष्ठा ocfs2_refcount_block *rb,
				     पूर्णांक index)
अणु
	क्रमागत ocfs2_ref_rec_contig contig =
				ocfs2_refcount_rec_contig(rb, index);

	अगर (contig == REF_CONTIG_NONE)
		वापस;

	अगर (contig == REF_CONTIG_LEFT || contig == REF_CONTIG_LEFTRIGHT) अणु
		BUG_ON(index == 0);
		index--;
	पूर्ण

	ocfs2_rotate_refcount_rec_left(rb, index);

	अगर (contig == REF_CONTIG_LEFTRIGHT)
		ocfs2_rotate_refcount_rec_left(rb, index);
पूर्ण

/*
 * Change the refcount indexed by "index" in ref_bh.
 * If refcount reaches 0, हटाओ it.
 */
अटल पूर्णांक ocfs2_change_refcount_rec(handle_t *handle,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *ref_leaf_bh,
				     पूर्णांक index, पूर्णांक merge, पूर्णांक change)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_list *rl = &rb->rf_records;
	काष्ठा ocfs2_refcount_rec *rec = &rl->rl_recs[index];

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_change_refcount_rec(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		index, le32_to_cpu(rec->r_refcount), change);
	le32_add_cpu(&rec->r_refcount, change);

	अगर (!rec->r_refcount) अणु
		अगर (index != le16_to_cpu(rl->rl_used) - 1) अणु
			स_हटाओ(rec, rec + 1,
				(le16_to_cpu(rl->rl_used) - index - 1) *
				माप(काष्ठा ocfs2_refcount_rec));
			स_रखो(&rl->rl_recs[le16_to_cpu(rl->rl_used) - 1],
			       0, माप(काष्ठा ocfs2_refcount_rec));
		पूर्ण

		le16_add_cpu(&rl->rl_used, -1);
	पूर्ण अन्यथा अगर (merge)
		ocfs2_refcount_rec_merge(rb, index);

	ocfs2_journal_dirty(handle, ref_leaf_bh);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_expand_अंतरभूत_ref_root(handle_t *handle,
					काष्ठा ocfs2_caching_info *ci,
					काष्ठा buffer_head *ref_root_bh,
					काष्ठा buffer_head **ref_leaf_bh,
					काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret;
	u16 suballoc_bit_start;
	u32 num_got;
	u64 suballoc_loc, blkno;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_refcount_block *new_rb;
	काष्ठा ocfs2_refcount_block *root_rb =
			(काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;

	ret = ocfs2_journal_access_rb(handle, ci, ref_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_claim_metadata(handle, meta_ac, 1, &suballoc_loc,
				   &suballoc_bit_start, &num_got,
				   &blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	new_bh = sb_getblk(sb, blkno);
	अगर (new_bh == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(ci, new_bh);

	ret = ocfs2_journal_access_rb(handle, ci, new_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Initialize ocfs2_refcount_block.
	 * It should contain the same inक्रमmation as the old root.
	 * so just स_नकल it and change the corresponding field.
	 */
	स_नकल(new_bh->b_data, ref_root_bh->b_data, sb->s_blocksize);

	new_rb = (काष्ठा ocfs2_refcount_block *)new_bh->b_data;
	new_rb->rf_suballoc_slot = cpu_to_le16(meta_ac->ac_alloc_slot);
	new_rb->rf_suballoc_loc = cpu_to_le64(suballoc_loc);
	new_rb->rf_suballoc_bit = cpu_to_le16(suballoc_bit_start);
	new_rb->rf_blkno = cpu_to_le64(blkno);
	new_rb->rf_cpos = cpu_to_le32(0);
	new_rb->rf_parent = cpu_to_le64(ref_root_bh->b_blocknr);
	new_rb->rf_flags = cpu_to_le32(OCFS2_REFCOUNT_LEAF_FL);
	ocfs2_journal_dirty(handle, new_bh);

	/* Now change the root. */
	स_रखो(&root_rb->rf_list, 0, sb->s_blocksize -
	       दुरत्व(काष्ठा ocfs2_refcount_block, rf_list));
	root_rb->rf_list.l_count = cpu_to_le16(ocfs2_extent_recs_per_rb(sb));
	root_rb->rf_clusters = cpu_to_le32(1);
	root_rb->rf_list.l_next_मुक्त_rec = cpu_to_le16(1);
	root_rb->rf_list.l_recs[0].e_blkno = cpu_to_le64(blkno);
	root_rb->rf_list.l_recs[0].e_leaf_clusters = cpu_to_le16(1);
	root_rb->rf_flags = cpu_to_le32(OCFS2_REFCOUNT_TREE_FL);

	ocfs2_journal_dirty(handle, ref_root_bh);

	trace_ocfs2_expand_अंतरभूत_ref_root((अचिन्हित दीर्घ दीर्घ)blkno,
		le16_to_cpu(new_rb->rf_records.rl_used));

	*ref_leaf_bh = new_bh;
	new_bh = शून्य;
out:
	brअन्यथा(new_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_refcount_rec_no_पूर्णांकersect(काष्ठा ocfs2_refcount_rec *prev,
					   काष्ठा ocfs2_refcount_rec *next)
अणु
	अगर (ocfs2_get_ref_rec_low_cpos(prev) + le32_to_cpu(prev->r_clusters) <=
		ocfs2_get_ref_rec_low_cpos(next))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक cmp_refcount_rec_by_low_cpos(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ocfs2_refcount_rec *l = a, *r = b;
	u32 l_cpos = ocfs2_get_ref_rec_low_cpos(l);
	u32 r_cpos = ocfs2_get_ref_rec_low_cpos(r);

	अगर (l_cpos > r_cpos)
		वापस 1;
	अगर (l_cpos < r_cpos)
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_refcount_rec_by_cpos(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ocfs2_refcount_rec *l = a, *r = b;
	u64 l_cpos = le64_to_cpu(l->r_cpos);
	u64 r_cpos = le64_to_cpu(r->r_cpos);

	अगर (l_cpos > r_cpos)
		वापस 1;
	अगर (l_cpos < r_cpos)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम swap_refcount_rec(व्योम *a, व्योम *b, पूर्णांक size)
अणु
	काष्ठा ocfs2_refcount_rec *l = a, *r = b;

	swap(*l, *r);
पूर्ण

/*
 * The refcount cpos are ordered by their 64bit cpos,
 * But we will use the low 32 bit to be the e_cpos in the b-tree.
 * So we need to make sure that this pos isn't पूर्णांकersected with others.
 *
 * Note: The refcount block is alपढ़ोy sorted by their low 32 bit cpos,
 *       So just try the middle pos first, and we will निकास when we find
 *       the good position.
 */
अटल पूर्णांक ocfs2_find_refcount_split_pos(काष्ठा ocfs2_refcount_list *rl,
					 u32 *split_pos, पूर्णांक *split_index)
अणु
	पूर्णांक num_used = le16_to_cpu(rl->rl_used);
	पूर्णांक delta, middle = num_used / 2;

	क्रम (delta = 0; delta < middle; delta++) अणु
		/* Let's check delta earlier than middle */
		अगर (ocfs2_refcount_rec_no_पूर्णांकersect(
					&rl->rl_recs[middle - delta - 1],
					&rl->rl_recs[middle - delta])) अणु
			*split_index = middle - delta;
			अवरोध;
		पूर्ण

		/* For even counts, करोn't walk off the end */
		अगर ((middle + delta + 1) == num_used)
			जारी;

		/* Now try delta past middle */
		अगर (ocfs2_refcount_rec_no_पूर्णांकersect(
					&rl->rl_recs[middle + delta],
					&rl->rl_recs[middle + delta + 1])) अणु
			*split_index = middle + delta + 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (delta >= middle)
		वापस -ENOSPC;

	*split_pos = ocfs2_get_ref_rec_low_cpos(&rl->rl_recs[*split_index]);
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_भागide_leaf_refcount_block(काष्ठा buffer_head *ref_leaf_bh,
					    काष्ठा buffer_head *new_bh,
					    u32 *split_cpos)
अणु
	पूर्णांक split_index = 0, num_moved, ret;
	u32 cpos = 0;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_list *rl = &rb->rf_records;
	काष्ठा ocfs2_refcount_block *new_rb =
			(काष्ठा ocfs2_refcount_block *)new_bh->b_data;
	काष्ठा ocfs2_refcount_list *new_rl = &new_rb->rf_records;

	trace_ocfs2_भागide_leaf_refcount_block(
		(अचिन्हित दीर्घ दीर्घ)ref_leaf_bh->b_blocknr,
		le16_to_cpu(rl->rl_count), le16_to_cpu(rl->rl_used));

	/*
	 * XXX: Improvement later.
	 * If we know all the high 32 bit cpos is the same, no need to sort.
	 *
	 * In order to make the whole process safe, we करो:
	 * 1. sort the entries by their low 32 bit cpos first so that we can
	 *    find the split cpos easily.
	 * 2. call ocfs2_insert_extent to insert the new refcount block.
	 * 3. move the refcount rec to the new block.
	 * 4. sort the entries by their 64 bit cpos.
	 * 5. dirty the new_rb and rb.
	 */
	sort(&rl->rl_recs, le16_to_cpu(rl->rl_used),
	     माप(काष्ठा ocfs2_refcount_rec),
	     cmp_refcount_rec_by_low_cpos, swap_refcount_rec);

	ret = ocfs2_find_refcount_split_pos(rl, &cpos, &split_index);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	new_rb->rf_cpos = cpu_to_le32(cpos);

	/* move refcount records starting from split_index to the new block. */
	num_moved = le16_to_cpu(rl->rl_used) - split_index;
	स_नकल(new_rl->rl_recs, &rl->rl_recs[split_index],
	       num_moved * माप(काष्ठा ocfs2_refcount_rec));

	/*ok, हटाओ the entries we just moved over to the other block. */
	स_रखो(&rl->rl_recs[split_index], 0,
	       num_moved * माप(काष्ठा ocfs2_refcount_rec));

	/* change old and new rl_used accordingly. */
	le16_add_cpu(&rl->rl_used, -num_moved);
	new_rl->rl_used = cpu_to_le16(num_moved);

	sort(&rl->rl_recs, le16_to_cpu(rl->rl_used),
	     माप(काष्ठा ocfs2_refcount_rec),
	     cmp_refcount_rec_by_cpos, swap_refcount_rec);

	sort(&new_rl->rl_recs, le16_to_cpu(new_rl->rl_used),
	     माप(काष्ठा ocfs2_refcount_rec),
	     cmp_refcount_rec_by_cpos, swap_refcount_rec);

	*split_cpos = cpos;
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_new_leaf_refcount_block(handle_t *handle,
					 काष्ठा ocfs2_caching_info *ci,
					 काष्ठा buffer_head *ref_root_bh,
					 काष्ठा buffer_head *ref_leaf_bh,
					 काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret;
	u16 suballoc_bit_start;
	u32 num_got, new_cpos;
	u64 suballoc_loc, blkno;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा ocfs2_refcount_block *root_rb =
			(काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_refcount_block *new_rb;
	काष्ठा ocfs2_extent_tree ref_et;

	BUG_ON(!(le32_to_cpu(root_rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL));

	ret = ocfs2_journal_access_rb(handle, ci, ref_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_claim_metadata(handle, meta_ac, 1, &suballoc_loc,
				   &suballoc_bit_start, &num_got,
				   &blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	new_bh = sb_getblk(sb, blkno);
	अगर (new_bh == शून्य) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(ci, new_bh);

	ret = ocfs2_journal_access_rb(handle, ci, new_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Initialize ocfs2_refcount_block. */
	new_rb = (काष्ठा ocfs2_refcount_block *)new_bh->b_data;
	स_रखो(new_rb, 0, sb->s_blocksize);
	म_नकल((व्योम *)new_rb, OCFS2_REFCOUNT_BLOCK_SIGNATURE);
	new_rb->rf_suballoc_slot = cpu_to_le16(meta_ac->ac_alloc_slot);
	new_rb->rf_suballoc_loc = cpu_to_le64(suballoc_loc);
	new_rb->rf_suballoc_bit = cpu_to_le16(suballoc_bit_start);
	new_rb->rf_fs_generation = cpu_to_le32(OCFS2_SB(sb)->fs_generation);
	new_rb->rf_blkno = cpu_to_le64(blkno);
	new_rb->rf_parent = cpu_to_le64(ref_root_bh->b_blocknr);
	new_rb->rf_flags = cpu_to_le32(OCFS2_REFCOUNT_LEAF_FL);
	new_rb->rf_records.rl_count =
				cpu_to_le16(ocfs2_refcount_recs_per_rb(sb));
	new_rb->rf_generation = root_rb->rf_generation;

	ret = ocfs2_भागide_leaf_refcount_block(ref_leaf_bh, new_bh, &new_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_journal_dirty(handle, ref_leaf_bh);
	ocfs2_journal_dirty(handle, new_bh);

	ocfs2_init_refcount_extent_tree(&ref_et, ci, ref_root_bh);

	trace_ocfs2_new_leaf_refcount_block(
			(अचिन्हित दीर्घ दीर्घ)new_bh->b_blocknr, new_cpos);

	/* Insert the new leaf block with the specअगरic offset cpos. */
	ret = ocfs2_insert_extent(handle, &ref_et, new_cpos, new_bh->b_blocknr,
				  1, 0, meta_ac);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	brअन्यथा(new_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_expand_refcount_tree(handle_t *handle,
				      काष्ठा ocfs2_caching_info *ci,
				      काष्ठा buffer_head *ref_root_bh,
				      काष्ठा buffer_head *ref_leaf_bh,
				      काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *expand_bh = शून्य;

	अगर (ref_root_bh == ref_leaf_bh) अणु
		/*
		 * the old root bh hasn't been expanded to a b-tree,
		 * so expand it first.
		 */
		ret = ocfs2_expand_अंतरभूत_ref_root(handle, ci, ref_root_bh,
						   &expand_bh, meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		expand_bh = ref_leaf_bh;
		get_bh(expand_bh);
	पूर्ण


	/* Now add a new refcount block पूर्णांकo the tree.*/
	ret = ocfs2_new_leaf_refcount_block(handle, ci, ref_root_bh,
					    expand_bh, meta_ac);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
out:
	brअन्यथा(expand_bh);
	वापस ret;
पूर्ण

/*
 * Adjust the extent rec in b-tree representing ref_leaf_bh.
 *
 * Only called when we have inserted a new refcount rec at index 0
 * which means ocfs2_extent_rec.e_cpos may need some change.
 */
अटल पूर्णांक ocfs2_adjust_refcount_rec(handle_t *handle,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *ref_root_bh,
				     काष्ठा buffer_head *ref_leaf_bh,
				     काष्ठा ocfs2_refcount_rec *rec)
अणु
	पूर्णांक ret = 0, i;
	u32 new_cpos, old_cpos;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_refcount_block *rb =
		(काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	काष्ठा ocfs2_extent_list *el;

	अगर (!(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL))
		जाओ out;

	rb = (काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	old_cpos = le32_to_cpu(rb->rf_cpos);
	new_cpos = le64_to_cpu(rec->r_cpos) & OCFS2_32BIT_POS_MASK;
	अगर (old_cpos <= new_cpos)
		जाओ out;

	ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);

	path = ocfs2_new_path_from_et(&et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(ci, path, old_cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * 2 more credits, one क्रम the leaf refcount block, one क्रम
	 * the extent block contains the extent rec.
	 */
	ret = ocfs2_extend_trans(handle, 2);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_eb(handle, ci, path_leaf_bh(path),
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* change the leaf extent block first. */
	el = path_leaf_el(path);

	क्रम (i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++)
		अगर (le32_to_cpu(el->l_recs[i].e_cpos) == old_cpos)
			अवरोध;

	BUG_ON(i == le16_to_cpu(el->l_next_मुक्त_rec));

	el->l_recs[i].e_cpos = cpu_to_le32(new_cpos);

	/* change the r_cpos in the leaf block. */
	rb->rf_cpos = cpu_to_le32(new_cpos);

	ocfs2_journal_dirty(handle, path_leaf_bh(path));
	ocfs2_journal_dirty(handle, ref_leaf_bh);

out:
	ocfs2_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_insert_refcount_rec(handle_t *handle,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *ref_root_bh,
				     काष्ठा buffer_head *ref_leaf_bh,
				     काष्ठा ocfs2_refcount_rec *rec,
				     पूर्णांक index, पूर्णांक merge,
				     काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_list *rf_list = &rb->rf_records;
	काष्ठा buffer_head *new_bh = शून्य;

	BUG_ON(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL);

	अगर (rf_list->rl_used == rf_list->rl_count) अणु
		u64 cpos = le64_to_cpu(rec->r_cpos);
		u32 len = le32_to_cpu(rec->r_clusters);

		ret = ocfs2_expand_refcount_tree(handle, ci, ref_root_bh,
						 ref_leaf_bh, meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, शून्य, &index,
					     &new_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ref_leaf_bh = new_bh;
		rb = (काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
		rf_list = &rb->rf_records;
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (index < le16_to_cpu(rf_list->rl_used))
		स_हटाओ(&rf_list->rl_recs[index + 1],
			&rf_list->rl_recs[index],
			(le16_to_cpu(rf_list->rl_used) - index) *
			 माप(काष्ठा ocfs2_refcount_rec));

	trace_ocfs2_insert_refcount_rec(
		(अचिन्हित दीर्घ दीर्घ)ref_leaf_bh->b_blocknr, index,
		(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(rec->r_cpos),
		le32_to_cpu(rec->r_clusters), le32_to_cpu(rec->r_refcount));

	rf_list->rl_recs[index] = *rec;

	le16_add_cpu(&rf_list->rl_used, 1);

	अगर (merge)
		ocfs2_refcount_rec_merge(rb, index);

	ocfs2_journal_dirty(handle, ref_leaf_bh);

	अगर (index == 0) अणु
		ret = ocfs2_adjust_refcount_rec(handle, ci,
						ref_root_bh,
						ref_leaf_bh, rec);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
out:
	brअन्यथा(new_bh);
	वापस ret;
पूर्ण

/*
 * Split the refcount_rec indexed by "index" in ref_leaf_bh.
 * This is much simple than our b-tree code.
 * split_rec is the new refcount rec we want to insert.
 * If split_rec->r_refcount > 0, we are changing the refcount(in हाल we
 * increase refcount or decrease a refcount to non-zero).
 * If split_rec->r_refcount == 0, we are punching a hole in current refcount
 * rec( in हाल we decrease a refcount to zero).
 */
अटल पूर्णांक ocfs2_split_refcount_rec(handle_t *handle,
				    काष्ठा ocfs2_caching_info *ci,
				    काष्ठा buffer_head *ref_root_bh,
				    काष्ठा buffer_head *ref_leaf_bh,
				    काष्ठा ocfs2_refcount_rec *split_rec,
				    पूर्णांक index, पूर्णांक merge,
				    काष्ठा ocfs2_alloc_context *meta_ac,
				    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret, recs_need;
	u32 len;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_list *rf_list = &rb->rf_records;
	काष्ठा ocfs2_refcount_rec *orig_rec = &rf_list->rl_recs[index];
	काष्ठा ocfs2_refcount_rec *tail_rec = शून्य;
	काष्ठा buffer_head *new_bh = शून्य;

	BUG_ON(le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL);

	trace_ocfs2_split_refcount_rec(le64_to_cpu(orig_rec->r_cpos),
		le32_to_cpu(orig_rec->r_clusters),
		le32_to_cpu(orig_rec->r_refcount),
		le64_to_cpu(split_rec->r_cpos),
		le32_to_cpu(split_rec->r_clusters),
		le32_to_cpu(split_rec->r_refcount));

	/*
	 * If we just need to split the header or tail clusters,
	 * no more recs are needed, just split is OK.
	 * Otherwise we at least need one new recs.
	 */
	अगर (!split_rec->r_refcount &&
	    (split_rec->r_cpos == orig_rec->r_cpos ||
	     le64_to_cpu(split_rec->r_cpos) +
	     le32_to_cpu(split_rec->r_clusters) ==
	     le64_to_cpu(orig_rec->r_cpos) + le32_to_cpu(orig_rec->r_clusters)))
		recs_need = 0;
	अन्यथा
		recs_need = 1;

	/*
	 * We need one more rec अगर we split in the middle and the new rec have
	 * some refcount in it.
	 */
	अगर (split_rec->r_refcount &&
	    (split_rec->r_cpos != orig_rec->r_cpos &&
	     le64_to_cpu(split_rec->r_cpos) +
	     le32_to_cpu(split_rec->r_clusters) !=
	     le64_to_cpu(orig_rec->r_cpos) + le32_to_cpu(orig_rec->r_clusters)))
		recs_need++;

	/* If the leaf block करोn't have enough record, expand it. */
	अगर (le16_to_cpu(rf_list->rl_used) + recs_need >
					 le16_to_cpu(rf_list->rl_count)) अणु
		काष्ठा ocfs2_refcount_rec पंचांगp_rec;
		u64 cpos = le64_to_cpu(orig_rec->r_cpos);
		len = le32_to_cpu(orig_rec->r_clusters);
		ret = ocfs2_expand_refcount_tree(handle, ci, ref_root_bh,
						 ref_leaf_bh, meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * We have to re-get it since now cpos may be moved to
		 * another leaf block.
		 */
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &पंचांगp_rec, &index,
					     &new_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		ref_leaf_bh = new_bh;
		rb = (काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
		rf_list = &rb->rf_records;
		orig_rec = &rf_list->rl_recs[index];
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, ci, ref_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * We have calculated out how many new records we need and store
	 * in recs_need, so spare enough space first by moving the records
	 * after "index" to the end.
	 */
	अगर (index != le16_to_cpu(rf_list->rl_used) - 1)
		स_हटाओ(&rf_list->rl_recs[index + 1 + recs_need],
			&rf_list->rl_recs[index + 1],
			(le16_to_cpu(rf_list->rl_used) - index - 1) *
			 माप(काष्ठा ocfs2_refcount_rec));

	len = (le64_to_cpu(orig_rec->r_cpos) +
	      le32_to_cpu(orig_rec->r_clusters)) -
	      (le64_to_cpu(split_rec->r_cpos) +
	      le32_to_cpu(split_rec->r_clusters));

	/*
	 * If we have "len", the we will split in the tail and move it
	 * to the end of the space we have just spared.
	 */
	अगर (len) अणु
		tail_rec = &rf_list->rl_recs[index + recs_need];

		स_नकल(tail_rec, orig_rec, माप(काष्ठा ocfs2_refcount_rec));
		le64_add_cpu(&tail_rec->r_cpos,
			     le32_to_cpu(tail_rec->r_clusters) - len);
		tail_rec->r_clusters = cpu_to_le32(len);
	पूर्ण

	/*
	 * If the split pos isn't the same as the original one, we need to
	 * split in the head.
	 *
	 * Note: We have the chance that split_rec.r_refcount = 0,
	 * recs_need = 0 and len > 0, which means we just cut the head from
	 * the orig_rec and in that हाल we have करोne some modअगरication in
	 * orig_rec above, so the check क्रम r_cpos is faked.
	 */
	अगर (split_rec->r_cpos != orig_rec->r_cpos && tail_rec != orig_rec) अणु
		len = le64_to_cpu(split_rec->r_cpos) -
		      le64_to_cpu(orig_rec->r_cpos);
		orig_rec->r_clusters = cpu_to_le32(len);
		index++;
	पूर्ण

	le16_add_cpu(&rf_list->rl_used, recs_need);

	अगर (split_rec->r_refcount) अणु
		rf_list->rl_recs[index] = *split_rec;
		trace_ocfs2_split_refcount_rec_insert(
			(अचिन्हित दीर्घ दीर्घ)ref_leaf_bh->b_blocknr, index,
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(split_rec->r_cpos),
			le32_to_cpu(split_rec->r_clusters),
			le32_to_cpu(split_rec->r_refcount));

		अगर (merge)
			ocfs2_refcount_rec_merge(rb, index);
	पूर्ण

	ocfs2_journal_dirty(handle, ref_leaf_bh);

out:
	brअन्यथा(new_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_increase_refcount(handle_t *handle,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *ref_root_bh,
				     u64 cpos, u32 len, पूर्णांक merge,
				     काष्ठा ocfs2_alloc_context *meta_ac,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret = 0, index;
	काष्ठा buffer_head *ref_leaf_bh = शून्य;
	काष्ठा ocfs2_refcount_rec rec;
	अचिन्हित पूर्णांक set_len = 0;

	trace_ocfs2_increase_refcount_begin(
	     (अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
	     (अचिन्हित दीर्घ दीर्घ)cpos, len);

	जबतक (len) अणु
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &rec, &index,
					     &ref_leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		set_len = le32_to_cpu(rec.r_clusters);

		/*
		 * Here we may meet with 3 situations:
		 *
		 * 1. If we find an alपढ़ोy existing record, and the length
		 *    is the same, cool, we just need to increase the r_refcount
		 *    and it is OK.
		 * 2. If we find a hole, just insert it with r_refcount = 1.
		 * 3. If we are in the middle of one extent record, split
		 *    it.
		 */
		अगर (rec.r_refcount && le64_to_cpu(rec.r_cpos) == cpos &&
		    set_len <= len) अणु
			trace_ocfs2_increase_refcount_change(
				(अचिन्हित दीर्घ दीर्घ)cpos, set_len,
				le32_to_cpu(rec.r_refcount));
			ret = ocfs2_change_refcount_rec(handle, ci,
							ref_leaf_bh, index,
							merge, 1);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा अगर (!rec.r_refcount) अणु
			rec.r_refcount = cpu_to_le32(1);

			trace_ocfs2_increase_refcount_insert(
			     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(rec.r_cpos),
			     set_len);
			ret = ocfs2_insert_refcount_rec(handle, ci, ref_root_bh,
							ref_leaf_bh,
							&rec, index,
							merge, meta_ac);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण अन्यथा  अणु
			set_len = min((u64)(cpos + len),
				      le64_to_cpu(rec.r_cpos) + set_len) - cpos;
			rec.r_cpos = cpu_to_le64(cpos);
			rec.r_clusters = cpu_to_le32(set_len);
			le32_add_cpu(&rec.r_refcount, 1);

			trace_ocfs2_increase_refcount_split(
			     (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(rec.r_cpos),
			     set_len, le32_to_cpu(rec.r_refcount));
			ret = ocfs2_split_refcount_rec(handle, ci,
						       ref_root_bh, ref_leaf_bh,
						       &rec, index, merge,
						       meta_ac, dealloc);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

		cpos += set_len;
		len -= set_len;
		brअन्यथा(ref_leaf_bh);
		ref_leaf_bh = शून्य;
	पूर्ण

out:
	brअन्यथा(ref_leaf_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_हटाओ_refcount_extent(handle_t *handle,
				काष्ठा ocfs2_caching_info *ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा buffer_head *ref_leaf_bh,
				काष्ठा ocfs2_alloc_context *meta_ac,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_extent_tree et;

	BUG_ON(rb->rf_records.rl_used);

	trace_ocfs2_हटाओ_refcount_extent(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)ref_leaf_bh->b_blocknr,
		le32_to_cpu(rb->rf_cpos));

	ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);
	ret = ocfs2_हटाओ_extent(handle, &et, le32_to_cpu(rb->rf_cpos),
				  1, meta_ac, dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_हटाओ_from_cache(ci, ref_leaf_bh);

	/*
	 * add the मुक्तd block to the dealloc so that it will be मुक्तd
	 * when we run dealloc.
	 */
	ret = ocfs2_cache_block_dealloc(dealloc, EXTENT_ALLOC_SYSTEM_INODE,
					le16_to_cpu(rb->rf_suballoc_slot),
					le64_to_cpu(rb->rf_suballoc_loc),
					le64_to_cpu(rb->rf_blkno),
					le16_to_cpu(rb->rf_suballoc_bit));
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_rb(handle, ci, ref_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;

	le32_add_cpu(&rb->rf_clusters, -1);

	/*
	 * check whether we need to restore the root refcount block अगर
	 * there is no leaf extent block at atll.
	 */
	अगर (!rb->rf_list.l_next_मुक्त_rec) अणु
		BUG_ON(rb->rf_clusters);

		trace_ocfs2_restore_refcount_block(
		     (अचिन्हित दीर्घ दीर्घ)ref_root_bh->b_blocknr);

		rb->rf_flags = 0;
		rb->rf_parent = 0;
		rb->rf_cpos = 0;
		स_रखो(&rb->rf_records, 0, sb->s_blocksize -
		       दुरत्व(काष्ठा ocfs2_refcount_block, rf_records));
		rb->rf_records.rl_count =
				cpu_to_le16(ocfs2_refcount_recs_per_rb(sb));
	पूर्ण

	ocfs2_journal_dirty(handle, ref_root_bh);

out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_increase_refcount(handle_t *handle,
			    काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *ref_root_bh,
			    u64 cpos, u32 len,
			    काष्ठा ocfs2_alloc_context *meta_ac,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	वापस __ocfs2_increase_refcount(handle, ci, ref_root_bh,
					 cpos, len, 1,
					 meta_ac, dealloc);
पूर्ण

अटल पूर्णांक ocfs2_decrease_refcount_rec(handle_t *handle,
				काष्ठा ocfs2_caching_info *ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा buffer_head *ref_leaf_bh,
				पूर्णांक index, u64 cpos, अचिन्हित पूर्णांक len,
				काष्ठा ocfs2_alloc_context *meta_ac,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_refcount_block *rb =
			(काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;
	काष्ठा ocfs2_refcount_rec *rec = &rb->rf_records.rl_recs[index];

	BUG_ON(cpos < le64_to_cpu(rec->r_cpos));
	BUG_ON(cpos + len >
	       le64_to_cpu(rec->r_cpos) + le32_to_cpu(rec->r_clusters));

	trace_ocfs2_decrease_refcount_rec(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)cpos, len);

	अगर (cpos == le64_to_cpu(rec->r_cpos) &&
	    len == le32_to_cpu(rec->r_clusters))
		ret = ocfs2_change_refcount_rec(handle, ci,
						ref_leaf_bh, index, 1, -1);
	अन्यथा अणु
		काष्ठा ocfs2_refcount_rec split = *rec;
		split.r_cpos = cpu_to_le64(cpos);
		split.r_clusters = cpu_to_le32(len);

		le32_add_cpu(&split.r_refcount, -1);

		ret = ocfs2_split_refcount_rec(handle, ci,
					       ref_root_bh, ref_leaf_bh,
					       &split, index, 1,
					       meta_ac, dealloc);
	पूर्ण

	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Remove the leaf refcount block अगर it contains no refcount record. */
	अगर (!rb->rf_records.rl_used && ref_leaf_bh != ref_root_bh) अणु
		ret = ocfs2_हटाओ_refcount_extent(handle, ci, ref_root_bh,
						   ref_leaf_bh, meta_ac,
						   dealloc);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_decrease_refcount(handle_t *handle,
				     काष्ठा ocfs2_caching_info *ci,
				     काष्ठा buffer_head *ref_root_bh,
				     u64 cpos, u32 len,
				     काष्ठा ocfs2_alloc_context *meta_ac,
				     काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
				     पूर्णांक delete)
अणु
	पूर्णांक ret = 0, index = 0;
	काष्ठा ocfs2_refcount_rec rec;
	अचिन्हित पूर्णांक r_count = 0, r_len;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(ci);
	काष्ठा buffer_head *ref_leaf_bh = शून्य;

	trace_ocfs2_decrease_refcount(
		(अचिन्हित दीर्घ दीर्घ)ocfs2_metadata_cache_owner(ci),
		(अचिन्हित दीर्घ दीर्घ)cpos, len, delete);

	जबतक (len) अणु
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, len, &rec, &index,
					     &ref_leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		r_count = le32_to_cpu(rec.r_refcount);
		BUG_ON(r_count == 0);
		अगर (!delete)
			BUG_ON(r_count > 1);

		r_len = min((u64)(cpos + len), le64_to_cpu(rec.r_cpos) +
			      le32_to_cpu(rec.r_clusters)) - cpos;

		ret = ocfs2_decrease_refcount_rec(handle, ci, ref_root_bh,
						  ref_leaf_bh, index,
						  cpos, r_len,
						  meta_ac, dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (le32_to_cpu(rec.r_refcount) == 1 && delete) अणु
			ret = ocfs2_cache_cluster_dealloc(dealloc,
					  ocfs2_clusters_to_blocks(sb, cpos),
							  r_len);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

		cpos += r_len;
		len -= r_len;
		brअन्यथा(ref_leaf_bh);
		ref_leaf_bh = शून्य;
	पूर्ण

out:
	brअन्यथा(ref_leaf_bh);
	वापस ret;
पूर्ण

/* Caller must hold refcount tree lock. */
पूर्णांक ocfs2_decrease_refcount(काष्ठा inode *inode,
			    handle_t *handle, u32 cpos, u32 len,
			    काष्ठा ocfs2_alloc_context *meta_ac,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			    पूर्णांक delete)
अणु
	पूर्णांक ret;
	u64 ref_blkno;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_tree *tree;

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_get_refcount_block(inode, &ref_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_get_refcount_tree(OCFS2_SB(inode->i_sb), ref_blkno, &tree);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_refcount_block(&tree->rf_ci, tree->rf_blkno,
					&ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = __ocfs2_decrease_refcount(handle, &tree->rf_ci, ref_root_bh,
					cpos, len, meta_ac, dealloc, delete);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
out:
	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

/*
 * Mark the alपढ़ोy-existing extent at cpos as refcounted क्रम len clusters.
 * This adds the refcount extent flag.
 *
 * If the existing extent is larger than the request, initiate a
 * split. An attempt will be made at merging with adjacent extents.
 *
 * The caller is responsible क्रम passing करोwn meta_ac अगर we'll need it.
 */
अटल पूर्णांक ocfs2_mark_extent_refcounted(काष्ठा inode *inode,
				काष्ठा ocfs2_extent_tree *et,
				handle_t *handle, u32 cpos,
				u32 len, u32 phys,
				काष्ठा ocfs2_alloc_context *meta_ac,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret;

	trace_ocfs2_mark_extent_refcounted(OCFS2_I(inode)->ip_blkno,
					   cpos, len, phys);

	अगर (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb))) अणु
		ret = ocfs2_error(inode->i_sb, "Inode %lu want to use refcount tree, but the feature bit is not set in the super block\n",
				  inode->i_ino);
		जाओ out;
	पूर्ण

	ret = ocfs2_change_extent_flag(handle, et, cpos,
				       len, phys, meta_ac, dealloc,
				       OCFS2_EXT_REFCOUNTED, 0);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

/*
 * Given some contiguous physical clusters, calculate what we need
 * क्रम modअगरying their refcount.
 */
अटल पूर्णांक ocfs2_calc_refcount_meta_credits(काष्ठा super_block *sb,
					    काष्ठा ocfs2_caching_info *ci,
					    काष्ठा buffer_head *ref_root_bh,
					    u64 start_cpos,
					    u32 clusters,
					    पूर्णांक *meta_add,
					    पूर्णांक *credits)
अणु
	पूर्णांक ret = 0, index, ref_blocks = 0, recs_add = 0;
	u64 cpos = start_cpos;
	काष्ठा ocfs2_refcount_block *rb;
	काष्ठा ocfs2_refcount_rec rec;
	काष्ठा buffer_head *ref_leaf_bh = शून्य, *prev_bh = शून्य;
	u32 len;

	जबतक (clusters) अणु
		ret = ocfs2_get_refcount_rec(ci, ref_root_bh,
					     cpos, clusters, &rec,
					     &index, &ref_leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (ref_leaf_bh != prev_bh) अणु
			/*
			 * Now we encounter a new leaf block, so calculate
			 * whether we need to extend the old leaf.
			 */
			अगर (prev_bh) अणु
				rb = (काष्ठा ocfs2_refcount_block *)
							prev_bh->b_data;

				अगर (le16_to_cpu(rb->rf_records.rl_used) +
				    recs_add >
				    le16_to_cpu(rb->rf_records.rl_count))
					ref_blocks++;
			पूर्ण

			recs_add = 0;
			*credits += 1;
			brअन्यथा(prev_bh);
			prev_bh = ref_leaf_bh;
			get_bh(prev_bh);
		पूर्ण

		trace_ocfs2_calc_refcount_meta_credits_iterate(
				recs_add, (अचिन्हित दीर्घ दीर्घ)cpos, clusters,
				(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(rec.r_cpos),
				le32_to_cpu(rec.r_clusters),
				le32_to_cpu(rec.r_refcount), index);

		len = min((u64)cpos + clusters, le64_to_cpu(rec.r_cpos) +
			  le32_to_cpu(rec.r_clusters)) - cpos;
		/*
		 * We record all the records which will be inserted to the
		 * same refcount block, so that we can tell exactly whether
		 * we need a new refcount block or not.
		 *
		 * If we will insert a new one, this is easy and only happens
		 * during adding refcounted flag to the extent, so we करोn't
		 * have a chance of spliting. We just need one record.
		 *
		 * If the refcount rec alपढ़ोy exists, that would be a little
		 * complicated. we may have to:
		 * 1) split at the beginning अगर the start pos isn't aligned.
		 *    we need 1 more record in this हाल.
		 * 2) split पूर्णांक the end अगर the end pos isn't aligned.
		 *    we need 1 more record in this हाल.
		 * 3) split in the middle because of file प्रणाली fragmentation.
		 *    we need 2 more records in this हाल(we can't detect this
		 *    beक्रमehand, so always think of the worst हाल).
		 */
		अगर (rec.r_refcount) अणु
			recs_add += 2;
			/* Check whether we need a split at the beginning. */
			अगर (cpos == start_cpos &&
			    cpos != le64_to_cpu(rec.r_cpos))
				recs_add++;

			/* Check whether we need a split in the end. */
			अगर (cpos + clusters < le64_to_cpu(rec.r_cpos) +
			    le32_to_cpu(rec.r_clusters))
				recs_add++;
		पूर्ण अन्यथा
			recs_add++;

		brअन्यथा(ref_leaf_bh);
		ref_leaf_bh = शून्य;
		clusters -= len;
		cpos += len;
	पूर्ण

	अगर (prev_bh) अणु
		rb = (काष्ठा ocfs2_refcount_block *)prev_bh->b_data;

		अगर (le16_to_cpu(rb->rf_records.rl_used) + recs_add >
		    le16_to_cpu(rb->rf_records.rl_count))
			ref_blocks++;

		*credits += 1;
	पूर्ण

	अगर (!ref_blocks)
		जाओ out;

	*meta_add += ref_blocks;
	*credits += ref_blocks;

	/*
	 * So we may need ref_blocks to insert पूर्णांकo the tree.
	 * That also means we need to change the b-tree and add that number
	 * of records since we never merge them.
	 * We need one more block क्रम expansion since the new created leaf
	 * block is also full and needs split.
	 */
	rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	अगर (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL) अणु
		काष्ठा ocfs2_extent_tree et;

		ocfs2_init_refcount_extent_tree(&et, ci, ref_root_bh);
		*meta_add += ocfs2_extend_meta_needed(et.et_root_el);
		*credits += ocfs2_calc_extend_credits(sb,
						      et.et_root_el);
	पूर्ण अन्यथा अणु
		*credits += OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
		*meta_add += 1;
	पूर्ण

out:

	trace_ocfs2_calc_refcount_meta_credits(
		(अचिन्हित दीर्घ दीर्घ)start_cpos, clusters,
		*meta_add, *credits);
	brअन्यथा(ref_leaf_bh);
	brअन्यथा(prev_bh);
	वापस ret;
पूर्ण

/*
 * For refcount tree, we will decrease some contiguous clusters
 * refcount count, so just go through it to see how many blocks
 * we gonna touch and whether we need to create new blocks.
 *
 * Normally the refcount blocks store these refcount should be
 * contiguous also, so that we can get the number easily.
 * We will at most add split 2 refcount records and 2 more
 * refcount blocks, so just check it in a rough way.
 *
 * Caller must hold refcount tree lock.
 */
पूर्णांक ocfs2_prepare_refcount_change_क्रम_del(काष्ठा inode *inode,
					  u64 refcount_loc,
					  u64 phys_blkno,
					  u32 clusters,
					  पूर्णांक *credits,
					  पूर्णांक *ref_blocks)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_tree *tree;
	u64 start_cpos = ocfs2_blocks_to_clusters(inode->i_sb, phys_blkno);

	अगर (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb))) अणु
		ret = ocfs2_error(inode->i_sb, "Inode %lu want to use refcount tree, but the feature bit is not set in the super block\n",
				  inode->i_ino);
		जाओ out;
	पूर्ण

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_get_refcount_tree(OCFS2_SB(inode->i_sb),
				      refcount_loc, &tree);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_refcount_block(&tree->rf_ci, refcount_loc,
					&ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_calc_refcount_meta_credits(inode->i_sb,
					       &tree->rf_ci,
					       ref_root_bh,
					       start_cpos, clusters,
					       ref_blocks, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_prepare_refcount_change_क्रम_del(*ref_blocks, *credits);

out:
	brअन्यथा(ref_root_bh);
	वापस ret;
पूर्ण

#घोषणा	MAX_CONTIG_BYTES	1048576

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_cow_contig_clusters(काष्ठा super_block *sb)
अणु
	वापस ocfs2_clusters_क्रम_bytes(sb, MAX_CONTIG_BYTES);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_cow_contig_mask(काष्ठा super_block *sb)
अणु
	वापस ~(ocfs2_cow_contig_clusters(sb) - 1);
पूर्ण

/*
 * Given an extent that starts at 'start' and an I/O that starts at 'cpos',
 * find an offset (start + (n * contig_clusters)) that is बंदst to cpos
 * जबतक still being less than or equal to it.
 *
 * The goal is to अवरोध the extent at a multiple of contig_clusters.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_cow_align_start(काष्ठा super_block *sb,
						 अचिन्हित पूर्णांक start,
						 अचिन्हित पूर्णांक cpos)
अणु
	BUG_ON(start > cpos);

	वापस start + ((cpos - start) & ocfs2_cow_contig_mask(sb));
पूर्ण

/*
 * Given a cluster count of len, pad it out so that it is a multiple
 * of contig_clusters.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_cow_align_length(काष्ठा super_block *sb,
						  अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक padded =
		(len + (ocfs2_cow_contig_clusters(sb) - 1)) &
		ocfs2_cow_contig_mask(sb);

	/* Did we wrap? */
	अगर (padded < len)
		padded = अच_पूर्णांक_उच्च;

	वापस padded;
पूर्ण

/*
 * Calculate out the start and number of भव clusters we need to to CoW.
 *
 * cpos is vitual start cluster position we want to करो CoW in a
 * file and ग_लिखो_len is the cluster length.
 * max_cpos is the place where we want to stop CoW पूर्णांकentionally.
 *
 * Normal we will start CoW from the beginning of extent record cotaining cpos.
 * We try to अवरोध up extents on boundaries of MAX_CONTIG_BYTES so that we
 * get good I/O from the resulting extent tree.
 */
अटल पूर्णांक ocfs2_refcount_cal_cow_clusters(काष्ठा inode *inode,
					   काष्ठा ocfs2_extent_list *el,
					   u32 cpos,
					   u32 ग_लिखो_len,
					   u32 max_cpos,
					   u32 *cow_start,
					   u32 *cow_len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक tree_height = le16_to_cpu(el->l_tree_depth), i;
	काष्ठा buffer_head *eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb = शून्य;
	काष्ठा ocfs2_extent_rec *rec;
	अचिन्हित पूर्णांक want_clusters, rec_end = 0;
	पूर्णांक contig_clusters = ocfs2_cow_contig_clusters(inode->i_sb);
	पूर्णांक leaf_clusters;

	BUG_ON(cpos + ग_लिखो_len > max_cpos);

	अगर (tree_height > 0) अणु
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, cpos, &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ret = ocfs2_error(inode->i_sb,
					  "Inode %lu has non zero tree depth in leaf block %llu\n",
					  inode->i_ino,
					  (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			जाओ out;
		पूर्ण
	पूर्ण

	*cow_len = 0;
	क्रम (i = 0; i < le16_to_cpu(el->l_next_मुक्त_rec); i++) अणु
		rec = &el->l_recs[i];

		अगर (ocfs2_is_empty_extent(rec)) अणु
			mlog_bug_on_msg(i != 0, "Inode %lu has empty record in "
					"index %d\n", inode->i_ino, i);
			जारी;
		पूर्ण

		अगर (le32_to_cpu(rec->e_cpos) +
		    le16_to_cpu(rec->e_leaf_clusters) <= cpos)
			जारी;

		अगर (*cow_len == 0) अणु
			/*
			 * We should find a refcounted record in the
			 * first pass.
			 */
			BUG_ON(!(rec->e_flags & OCFS2_EXT_REFCOUNTED));
			*cow_start = le32_to_cpu(rec->e_cpos);
		पूर्ण

		/*
		 * If we encounter a hole, a non-refcounted record or
		 * pass the max_cpos, stop the search.
		 */
		अगर ((!(rec->e_flags & OCFS2_EXT_REFCOUNTED)) ||
		    (*cow_len && rec_end != le32_to_cpu(rec->e_cpos)) ||
		    (max_cpos <= le32_to_cpu(rec->e_cpos)))
			अवरोध;

		leaf_clusters = le16_to_cpu(rec->e_leaf_clusters);
		rec_end = le32_to_cpu(rec->e_cpos) + leaf_clusters;
		अगर (rec_end > max_cpos) अणु
			rec_end = max_cpos;
			leaf_clusters = rec_end - le32_to_cpu(rec->e_cpos);
		पूर्ण

		/*
		 * How many clusters करो we actually need from
		 * this extent?  First we see how many we actually
		 * need to complete the ग_लिखो.  If that's smaller
		 * than contig_clusters, we try क्रम contig_clusters.
		 */
		अगर (!*cow_len)
			want_clusters = ग_लिखो_len;
		अन्यथा
			want_clusters = (cpos + ग_लिखो_len) -
				(*cow_start + *cow_len);
		अगर (want_clusters < contig_clusters)
			want_clusters = contig_clusters;

		/*
		 * If the ग_लिखो करोes not cover the whole extent, we
		 * need to calculate how we're going to split the extent.
		 * We try to करो it on contig_clusters boundaries.
		 *
		 * Any extent smaller than contig_clusters will be
		 * CoWed in its entirety.
		 */
		अगर (leaf_clusters <= contig_clusters)
			*cow_len += leaf_clusters;
		अन्यथा अगर (*cow_len || (*cow_start == cpos)) अणु
			/*
			 * This extent needs to be CoW'd from its
			 * beginning, so all we have to करो is compute
			 * how many clusters to grab.  We align
			 * want_clusters to the edge of contig_clusters
			 * to get better I/O.
			 */
			want_clusters = ocfs2_cow_align_length(inode->i_sb,
							       want_clusters);

			अगर (leaf_clusters < want_clusters)
				*cow_len += leaf_clusters;
			अन्यथा
				*cow_len += want_clusters;
		पूर्ण अन्यथा अगर ((*cow_start + contig_clusters) >=
			   (cpos + ग_लिखो_len)) अणु
			/*
			 * Breaking off contig_clusters at the front
			 * of the extent will cover our ग_लिखो.  That's
			 * easy.
			 */
			*cow_len = contig_clusters;
		पूर्ण अन्यथा अगर ((rec_end - cpos) <= contig_clusters) अणु
			/*
			 * Breaking off contig_clusters at the tail of
			 * this extent will cover cpos.
			 */
			*cow_start = rec_end - contig_clusters;
			*cow_len = contig_clusters;
		पूर्ण अन्यथा अगर ((rec_end - cpos) <= want_clusters) अणु
			/*
			 * While we can't fit the entire ग_लिखो in this
			 * extent, we know that the ग_लिखो goes from cpos
			 * to the end of the extent.  Break that off.
			 * We try to अवरोध it at some multiple of
			 * contig_clusters from the front of the extent.
			 * Failing that (ie, cpos is within
			 * contig_clusters of the front), we'll CoW the
			 * entire extent.
			 */
			*cow_start = ocfs2_cow_align_start(inode->i_sb,
							   *cow_start, cpos);
			*cow_len = rec_end - *cow_start;
		पूर्ण अन्यथा अणु
			/*
			 * Ok, the entire ग_लिखो lives in the middle of
			 * this extent.  Let's try to slice the extent up
			 * nicely.  Optimally, our CoW region starts at
			 * m*contig_clusters from the beginning of the
			 * extent and goes क्रम n*contig_clusters,
			 * covering the entire ग_लिखो.
			 */
			*cow_start = ocfs2_cow_align_start(inode->i_sb,
							   *cow_start, cpos);

			want_clusters = (cpos + ग_लिखो_len) - *cow_start;
			want_clusters = ocfs2_cow_align_length(inode->i_sb,
							       want_clusters);
			अगर (*cow_start + want_clusters <= rec_end)
				*cow_len = want_clusters;
			अन्यथा
				*cow_len = rec_end - *cow_start;
		पूर्ण

		/* Have we covered our entire ग_लिखो yet? */
		अगर ((*cow_start + *cow_len) >= (cpos + ग_लिखो_len))
			अवरोध;

		/*
		 * If we reach the end of the extent block and करोn't get enough
		 * clusters, जारी with the next extent block अगर possible.
		 */
		अगर (i + 1 == le16_to_cpu(el->l_next_मुक्त_rec) &&
		    eb && eb->h_next_leaf_blk) अणु
			brअन्यथा(eb_bh);
			eb_bh = शून्य;

			ret = ocfs2_पढ़ो_extent_block(INODE_CACHE(inode),
					       le64_to_cpu(eb->h_next_leaf_blk),
					       &eb_bh);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
			el = &eb->h_list;
			i = -1;
		पूर्ण
	पूर्ण

out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

/*
 * Prepare meta_ac, data_ac and calculate credits when we want to add some
 * num_clusters in data_tree "et" and change the refcount क्रम the old
 * clusters(starting क्रमm p_cluster) in the refcount tree.
 *
 * Note:
 * 1. since we may split the old tree, so we at most will need num_clusters + 2
 *    more new leaf records.
 * 2. In some हाल, we may not need to reserve new clusters(e.g, reflink), so
 *    just give data_ac = शून्य.
 */
अटल पूर्णांक ocfs2_lock_refcount_allocators(काष्ठा super_block *sb,
					u32 p_cluster, u32 num_clusters,
					काष्ठा ocfs2_extent_tree *et,
					काष्ठा ocfs2_caching_info *ref_ci,
					काष्ठा buffer_head *ref_root_bh,
					काष्ठा ocfs2_alloc_context **meta_ac,
					काष्ठा ocfs2_alloc_context **data_ac,
					पूर्णांक *credits)
अणु
	पूर्णांक ret = 0, meta_add = 0;
	पूर्णांक num_मुक्त_extents = ocfs2_num_मुक्त_extents(et);

	अगर (num_मुक्त_extents < 0) अणु
		ret = num_मुक्त_extents;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (num_मुक्त_extents < num_clusters + 2)
		meta_add =
			ocfs2_extend_meta_needed(et->et_root_el);

	*credits += ocfs2_calc_extend_credits(sb, et->et_root_el);

	ret = ocfs2_calc_refcount_meta_credits(sb, ref_ci, ref_root_bh,
					       p_cluster, num_clusters,
					       &meta_add, credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_lock_refcount_allocators(meta_add, *credits);
	ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(sb), meta_add,
						meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (data_ac) अणु
		ret = ocfs2_reserve_clusters(OCFS2_SB(sb), num_clusters,
					     data_ac);
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

अटल पूर्णांक ocfs2_clear_cow_buffer(handle_t *handle, काष्ठा buffer_head *bh)
अणु
	BUG_ON(buffer_dirty(bh));

	clear_buffer_mapped(bh);

	वापस 0;
पूर्ण

पूर्णांक ocfs2_duplicate_clusters_by_page(handle_t *handle,
				     काष्ठा inode *inode,
				     u32 cpos, u32 old_cluster,
				     u32 new_cluster, u32 new_len)
अणु
	पूर्णांक ret = 0, partial;
	काष्ठा super_block *sb = inode->i_sb;
	u64 new_block = ocfs2_clusters_to_blocks(sb, new_cluster);
	काष्ठा page *page;
	pgoff_t page_index;
	अचिन्हित पूर्णांक from, to;
	loff_t offset, end, map_end;
	काष्ठा address_space *mapping = inode->i_mapping;

	trace_ocfs2_duplicate_clusters_by_page(cpos, old_cluster,
					       new_cluster, new_len);

	offset = ((loff_t)cpos) << OCFS2_SB(sb)->s_clustersize_bits;
	end = offset + (new_len << OCFS2_SB(sb)->s_clustersize_bits);
	/*
	 * We only duplicate pages until we reach the page contains i_size - 1.
	 * So trim 'end' to i_size.
	 */
	अगर (end > i_size_पढ़ो(inode))
		end = i_size_पढ़ो(inode);

	जबतक (offset < end) अणु
		page_index = offset >> PAGE_SHIFT;
		map_end = ((loff_t)page_index + 1) << PAGE_SHIFT;
		अगर (map_end > end)
			map_end = end;

		/* from, to is the offset within the page. */
		from = offset & (PAGE_SIZE - 1);
		to = PAGE_SIZE;
		अगर (map_end & (PAGE_SIZE - 1))
			to = map_end & (PAGE_SIZE - 1);

retry:
		page = find_or_create_page(mapping, page_index, GFP_NOFS);
		अगर (!page) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		/*
		 * In हाल PAGE_SIZE <= CLUSTER_SIZE, we करो not expect a dirty
		 * page, so ग_लिखो it back.
		 */
		अगर (PAGE_SIZE <= OCFS2_SB(sb)->s_clustersize) अणु
			अगर (PageDirty(page)) अणु
				/*
				 * ग_लिखो_on_page will unlock the page on वापस
				 */
				ret = ग_लिखो_one_page(page);
				जाओ retry;
			पूर्ण
		पूर्ण

		अगर (!PageUptodate(page)) अणु
			ret = block_पढ़ो_full_page(page, ocfs2_get_block);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ unlock;
			पूर्ण
			lock_page(page);
		पूर्ण

		अगर (page_has_buffers(page)) अणु
			ret = walk_page_buffers(handle, page_buffers(page),
						from, to, &partial,
						ocfs2_clear_cow_buffer);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ unlock;
			पूर्ण
		पूर्ण

		ocfs2_map_and_dirty_page(inode,
					 handle, from, to,
					 page, 0, &new_block);
		mark_page_accessed(page);
unlock:
		unlock_page(page);
		put_page(page);
		page = शून्य;
		offset = map_end;
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक ocfs2_duplicate_clusters_by_jbd(handle_t *handle,
				    काष्ठा inode *inode,
				    u32 cpos, u32 old_cluster,
				    u32 new_cluster, u32 new_len)
अणु
	पूर्णांक ret = 0;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा ocfs2_caching_info *ci = INODE_CACHE(inode);
	पूर्णांक i, blocks = ocfs2_clusters_to_blocks(sb, new_len);
	u64 old_block = ocfs2_clusters_to_blocks(sb, old_cluster);
	u64 new_block = ocfs2_clusters_to_blocks(sb, new_cluster);
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	काष्ठा buffer_head *old_bh = शून्य;
	काष्ठा buffer_head *new_bh = शून्य;

	trace_ocfs2_duplicate_clusters_by_page(cpos, old_cluster,
					       new_cluster, new_len);

	क्रम (i = 0; i < blocks; i++, old_block++, new_block++) अणु
		new_bh = sb_getblk(osb->sb, new_block);
		अगर (new_bh == शून्य) अणु
			ret = -ENOMEM;
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ocfs2_set_new_buffer_uptodate(ci, new_bh);

		ret = ocfs2_पढ़ो_block(ci, old_block, &old_bh, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		ret = ocfs2_journal_access(handle, ci, new_bh,
					   OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		स_नकल(new_bh->b_data, old_bh->b_data, sb->s_blocksize);
		ocfs2_journal_dirty(handle, new_bh);

		brअन्यथा(new_bh);
		brअन्यथा(old_bh);
		new_bh = शून्य;
		old_bh = शून्य;
	पूर्ण

	brअन्यथा(new_bh);
	brअन्यथा(old_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_clear_ext_refcount(handle_t *handle,
				    काष्ठा ocfs2_extent_tree *et,
				    u32 cpos, u32 p_cluster, u32 len,
				    अचिन्हित पूर्णांक ext_flags,
				    काष्ठा ocfs2_alloc_context *meta_ac,
				    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret, index;
	काष्ठा ocfs2_extent_rec replace_rec;
	काष्ठा ocfs2_path *path = शून्य;
	काष्ठा ocfs2_extent_list *el;
	काष्ठा super_block *sb = ocfs2_metadata_cache_get_super(et->et_ci);
	u64 ino = ocfs2_metadata_cache_owner(et->et_ci);

	trace_ocfs2_clear_ext_refcount((अचिन्हित दीर्घ दीर्घ)ino,
				       cpos, len, p_cluster, ext_flags);

	स_रखो(&replace_rec, 0, माप(replace_rec));
	replace_rec.e_cpos = cpu_to_le32(cpos);
	replace_rec.e_leaf_clusters = cpu_to_le16(len);
	replace_rec.e_blkno = cpu_to_le64(ocfs2_clusters_to_blocks(sb,
								   p_cluster));
	replace_rec.e_flags = ext_flags;
	replace_rec.e_flags &= ~OCFS2_EXT_REFCOUNTED;

	path = ocfs2_new_path_from_et(et);
	अगर (!path) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_find_path(et->et_ci, path, cpos);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	el = path_leaf_el(path);

	index = ocfs2_search_extent_list(el, cpos);
	अगर (index == -1) अणु
		ret = ocfs2_error(sb,
				  "Inode %llu has an extent at cpos %u which can no longer be found\n",
				  (अचिन्हित दीर्घ दीर्घ)ino, cpos);
		जाओ out;
	पूर्ण

	ret = ocfs2_split_extent(handle, et, path, index,
				 &replace_rec, meta_ac, dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	ocfs2_मुक्त_path(path);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_replace_clusters(handle_t *handle,
				  काष्ठा ocfs2_cow_context *context,
				  u32 cpos, u32 old,
				  u32 new, u32 len,
				  अचिन्हित पूर्णांक ext_flags)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_caching_info *ci = context->data_et.et_ci;
	u64 ino = ocfs2_metadata_cache_owner(ci);

	trace_ocfs2_replace_clusters((अचिन्हित दीर्घ दीर्घ)ino,
				     cpos, old, new, len, ext_flags);

	/*If the old clusters is unwritten, no need to duplicate. */
	अगर (!(ext_flags & OCFS2_EXT_UNWRITTEN)) अणु
		ret = context->cow_duplicate_clusters(handle, context->inode,
						      cpos, old, new, len);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = ocfs2_clear_ext_refcount(handle, &context->data_et,
				       cpos, new, len, ext_flags,
				       context->meta_ac, &context->dealloc);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
out:
	वापस ret;
पूर्ण

पूर्णांक ocfs2_cow_sync_ग_लिखोback(काष्ठा super_block *sb,
			     काष्ठा inode *inode,
			     u32 cpos, u32 num_clusters)
अणु
	पूर्णांक ret = 0;
	loff_t offset, end, map_end;
	pgoff_t page_index;
	काष्ठा page *page;

	अगर (ocfs2_should_order_data(inode))
		वापस 0;

	offset = ((loff_t)cpos) << OCFS2_SB(sb)->s_clustersize_bits;
	end = offset + (num_clusters << OCFS2_SB(sb)->s_clustersize_bits);

	ret = filemap_fdataग_लिखो_range(inode->i_mapping,
				       offset, end - 1);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	जबतक (offset < end) अणु
		page_index = offset >> PAGE_SHIFT;
		map_end = ((loff_t)page_index + 1) << PAGE_SHIFT;
		अगर (map_end > end)
			map_end = end;

		page = find_or_create_page(inode->i_mapping,
					   page_index, GFP_NOFS);
		BUG_ON(!page);

		रुको_on_page_ग_लिखोback(page);
		अगर (PageError(page)) अणु
			ret = -EIO;
			mlog_त्रुटि_सं(ret);
		पूर्ण अन्यथा
			mark_page_accessed(page);

		unlock_page(page);
		put_page(page);
		page = शून्य;
		offset = map_end;
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_di_get_clusters(काष्ठा ocfs2_cow_context *context,
				 u32 v_cluster, u32 *p_cluster,
				 u32 *num_clusters,
				 अचिन्हित पूर्णांक *extent_flags)
अणु
	वापस ocfs2_get_clusters(context->inode, v_cluster, p_cluster,
				  num_clusters, extent_flags);
पूर्ण

अटल पूर्णांक ocfs2_make_clusters_writable(काष्ठा super_block *sb,
					काष्ठा ocfs2_cow_context *context,
					u32 cpos, u32 p_cluster,
					u32 num_clusters, अचिन्हित पूर्णांक e_flags)
अणु
	पूर्णांक ret, delete, index, credits =  0;
	u32 new_bit, new_len, orig_num_clusters;
	अचिन्हित पूर्णांक set_len;
	काष्ठा ocfs2_super *osb = OCFS2_SB(sb);
	handle_t *handle;
	काष्ठा buffer_head *ref_leaf_bh = शून्य;
	काष्ठा ocfs2_caching_info *ref_ci = &context->ref_tree->rf_ci;
	काष्ठा ocfs2_refcount_rec rec;

	trace_ocfs2_make_clusters_writable(cpos, p_cluster,
					   num_clusters, e_flags);

	ret = ocfs2_lock_refcount_allocators(sb, p_cluster, num_clusters,
					     &context->data_et,
					     ref_ci,
					     context->ref_root_bh,
					     &context->meta_ac,
					     &context->data_ac, &credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	अगर (context->post_refcount)
		credits += context->post_refcount->credits;

	credits += context->extra_credits;
	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	orig_num_clusters = num_clusters;

	जबतक (num_clusters) अणु
		ret = ocfs2_get_refcount_rec(ref_ci, context->ref_root_bh,
					     p_cluster, num_clusters,
					     &rec, &index, &ref_leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण

		BUG_ON(!rec.r_refcount);
		set_len = min((u64)p_cluster + num_clusters,
			      le64_to_cpu(rec.r_cpos) +
			      le32_to_cpu(rec.r_clusters)) - p_cluster;

		/*
		 * There are many dअगरferent situation here.
		 * 1. If refcount == 1, हटाओ the flag and करोn't COW.
		 * 2. If refcount > 1, allocate clusters.
		 *    Here we may not allocate r_len once at a समय, so जारी
		 *    until we reach num_clusters.
		 */
		अगर (le32_to_cpu(rec.r_refcount) == 1) अणु
			delete = 0;
			ret = ocfs2_clear_ext_refcount(handle,
						       &context->data_et,
						       cpos, p_cluster,
						       set_len, e_flags,
						       context->meta_ac,
						       &context->dealloc);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out_commit;
			पूर्ण
		पूर्ण अन्यथा अणु
			delete = 1;

			ret = __ocfs2_claim_clusters(handle,
						     context->data_ac,
						     1, set_len,
						     &new_bit, &new_len);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out_commit;
			पूर्ण

			ret = ocfs2_replace_clusters(handle, context,
						     cpos, p_cluster, new_bit,
						     new_len, e_flags);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out_commit;
			पूर्ण
			set_len = new_len;
		पूर्ण

		ret = __ocfs2_decrease_refcount(handle, ref_ci,
						context->ref_root_bh,
						p_cluster, set_len,
						context->meta_ac,
						&context->dealloc, delete);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण

		cpos += set_len;
		p_cluster += set_len;
		num_clusters -= set_len;
		brअन्यथा(ref_leaf_bh);
		ref_leaf_bh = शून्य;
	पूर्ण

	/* handle any post_cow action. */
	अगर (context->post_refcount && context->post_refcount->func) अणु
		ret = context->post_refcount->func(context->inode, handle,
						context->post_refcount->para);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
	पूर्ण

	/*
	 * Here we should ग_लिखो the new page out first अगर we are
	 * in ग_लिखो-back mode.
	 */
	अगर (context->get_clusters == ocfs2_di_get_clusters) अणु
		ret = ocfs2_cow_sync_ग_लिखोback(sb, context->inode, cpos,
					       orig_num_clusters);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out_commit:
	ocfs2_commit_trans(osb, handle);

out:
	अगर (context->data_ac) अणु
		ocfs2_मुक्त_alloc_context(context->data_ac);
		context->data_ac = शून्य;
	पूर्ण
	अगर (context->meta_ac) अणु
		ocfs2_मुक्त_alloc_context(context->meta_ac);
		context->meta_ac = शून्य;
	पूर्ण
	brअन्यथा(ref_leaf_bh);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_replace_cow(काष्ठा ocfs2_cow_context *context)
अणु
	पूर्णांक ret = 0;
	काष्ठा inode *inode = context->inode;
	u32 cow_start = context->cow_start, cow_len = context->cow_len;
	u32 p_cluster, num_clusters;
	अचिन्हित पूर्णांक ext_flags;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);

	अगर (!ocfs2_refcount_tree(osb)) अणु
		वापस ocfs2_error(inode->i_sb, "Inode %lu want to use refcount tree, but the feature bit is not set in the super block\n",
				   inode->i_ino);
	पूर्ण

	ocfs2_init_dealloc_ctxt(&context->dealloc);

	जबतक (cow_len) अणु
		ret = context->get_clusters(context, cow_start, &p_cluster,
					    &num_clusters, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		BUG_ON(!(ext_flags & OCFS2_EXT_REFCOUNTED));

		अगर (cow_len < num_clusters)
			num_clusters = cow_len;

		ret = ocfs2_make_clusters_writable(inode->i_sb, context,
						   cow_start, p_cluster,
						   num_clusters, ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		cow_len -= num_clusters;
		cow_start += num_clusters;
	पूर्ण

	अगर (ocfs2_dealloc_has_cluster(&context->dealloc)) अणु
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &context->dealloc);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Starting at cpos, try to CoW ग_लिखो_len clusters.  Don't CoW
 * past max_cpos.  This will stop when it runs पूर्णांकo a hole or an
 * unrefcounted extent.
 */
अटल पूर्णांक ocfs2_refcount_cow_hunk(काष्ठा inode *inode,
				   काष्ठा buffer_head *di_bh,
				   u32 cpos, u32 ग_लिखो_len, u32 max_cpos)
अणु
	पूर्णांक ret;
	u32 cow_start = 0, cow_len = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_tree *ref_tree;
	काष्ठा ocfs2_cow_context *context = शून्य;

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_refcount_cal_cow_clusters(inode, &di->id2.i_list,
					      cpos, ग_लिखो_len, max_cpos,
					      &cow_start, &cow_len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_refcount_cow_hunk(OCFS2_I(inode)->ip_blkno,
				      cpos, ग_लिखो_len, max_cpos,
				      cow_start, cow_len);

	BUG_ON(cow_len == 0);

	context = kzalloc(माप(काष्ठा ocfs2_cow_context), GFP_NOFS);
	अगर (!context) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_lock_refcount_tree(osb, le64_to_cpu(di->i_refcount_loc),
				       1, &ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	context->inode = inode;
	context->cow_start = cow_start;
	context->cow_len = cow_len;
	context->ref_tree = ref_tree;
	context->ref_root_bh = ref_root_bh;
	context->cow_duplicate_clusters = ocfs2_duplicate_clusters_by_page;
	context->get_clusters = ocfs2_di_get_clusters;

	ocfs2_init_dinode_extent_tree(&context->data_et,
				      INODE_CACHE(inode), di_bh);

	ret = ocfs2_replace_cow(context);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	/*
	 * truncate the extent map here since no matter whether we meet with
	 * any error during the action, we shouldn't trust cached extent map
	 * any more.
	 */
	ocfs2_extent_map_trunc(inode, cow_start);

	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brअन्यथा(ref_root_bh);
out:
	kमुक्त(context);
	वापस ret;
पूर्ण

/*
 * CoW any and all clusters between cpos and cpos+ग_लिखो_len.
 * Don't CoW past max_cpos.  If this वापसs successfully, all
 * clusters between cpos and cpos+ग_लिखो_len are safe to modअगरy.
 */
पूर्णांक ocfs2_refcount_cow(काष्ठा inode *inode,
		       काष्ठा buffer_head *di_bh,
		       u32 cpos, u32 ग_लिखो_len, u32 max_cpos)
अणु
	पूर्णांक ret = 0;
	u32 p_cluster, num_clusters;
	अचिन्हित पूर्णांक ext_flags;

	जबतक (ग_लिखो_len) अणु
		ret = ocfs2_get_clusters(inode, cpos, &p_cluster,
					 &num_clusters, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			अवरोध;
		पूर्ण

		अगर (ग_लिखो_len < num_clusters)
			num_clusters = ग_लिखो_len;

		अगर (ext_flags & OCFS2_EXT_REFCOUNTED) अणु
			ret = ocfs2_refcount_cow_hunk(inode, di_bh, cpos,
						      num_clusters, max_cpos);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				अवरोध;
			पूर्ण
		पूर्ण

		ग_लिखो_len -= num_clusters;
		cpos += num_clusters;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_xattr_value_get_clusters(काष्ठा ocfs2_cow_context *context,
					  u32 v_cluster, u32 *p_cluster,
					  u32 *num_clusters,
					  अचिन्हित पूर्णांक *extent_flags)
अणु
	काष्ठा inode *inode = context->inode;
	काष्ठा ocfs2_xattr_value_root *xv = context->cow_object;

	वापस ocfs2_xattr_get_clusters(inode, v_cluster, p_cluster,
					num_clusters, &xv->xr_list,
					extent_flags);
पूर्ण

/*
 * Given a xattr value root, calculate the most meta/credits we need क्रम
 * refcount tree change अगर we truncate it to 0.
 */
पूर्णांक ocfs2_refcounted_xattr_delete_need(काष्ठा inode *inode,
				       काष्ठा ocfs2_caching_info *ref_ci,
				       काष्ठा buffer_head *ref_root_bh,
				       काष्ठा ocfs2_xattr_value_root *xv,
				       पूर्णांक *meta_add, पूर्णांक *credits)
अणु
	पूर्णांक ret = 0, index, ref_blocks = 0;
	u32 p_cluster, num_clusters;
	u32 cpos = 0, clusters = le32_to_cpu(xv->xr_clusters);
	काष्ठा ocfs2_refcount_block *rb;
	काष्ठा ocfs2_refcount_rec rec;
	काष्ठा buffer_head *ref_leaf_bh = शून्य;

	जबतक (cpos < clusters) अणु
		ret = ocfs2_xattr_get_clusters(inode, cpos, &p_cluster,
					       &num_clusters, &xv->xr_list,
					       शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		cpos += num_clusters;

		जबतक (num_clusters) अणु
			ret = ocfs2_get_refcount_rec(ref_ci, ref_root_bh,
						     p_cluster, num_clusters,
						     &rec, &index,
						     &ref_leaf_bh);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण

			BUG_ON(!rec.r_refcount);

			rb = (काष्ठा ocfs2_refcount_block *)ref_leaf_bh->b_data;

			/*
			 * We really करोn't know whether the other clusters is in
			 * this refcount block or not, so just take the worst
			 * हाल that all the clusters are in this block and each
			 * one will split a refcount rec, so totally we need
			 * clusters * 2 new refcount rec.
			 */
			अगर (le16_to_cpu(rb->rf_records.rl_used) + clusters * 2 >
			    le16_to_cpu(rb->rf_records.rl_count))
				ref_blocks++;

			*credits += 1;
			brअन्यथा(ref_leaf_bh);
			ref_leaf_bh = शून्य;

			अगर (num_clusters <= le32_to_cpu(rec.r_clusters))
				अवरोध;
			अन्यथा
				num_clusters -= le32_to_cpu(rec.r_clusters);
			p_cluster += num_clusters;
		पूर्ण
	पूर्ण

	*meta_add += ref_blocks;
	अगर (!ref_blocks)
		जाओ out;

	rb = (काष्ठा ocfs2_refcount_block *)ref_root_bh->b_data;
	अगर (le32_to_cpu(rb->rf_flags) & OCFS2_REFCOUNT_TREE_FL)
		*credits += OCFS2_EXPAND_REFCOUNT_TREE_CREDITS;
	अन्यथा अणु
		काष्ठा ocfs2_extent_tree et;

		ocfs2_init_refcount_extent_tree(&et, ref_ci, ref_root_bh);
		*credits += ocfs2_calc_extend_credits(inode->i_sb,
						      et.et_root_el);
	पूर्ण

out:
	brअन्यथा(ref_leaf_bh);
	वापस ret;
पूर्ण

/*
 * Do CoW क्रम xattr.
 */
पूर्णांक ocfs2_refcount_cow_xattr(काष्ठा inode *inode,
			     काष्ठा ocfs2_dinode *di,
			     काष्ठा ocfs2_xattr_value_buf *vb,
			     काष्ठा ocfs2_refcount_tree *ref_tree,
			     काष्ठा buffer_head *ref_root_bh,
			     u32 cpos, u32 ग_लिखो_len,
			     काष्ठा ocfs2_post_refcount *post)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_xattr_value_root *xv = vb->vb_xv;
	काष्ठा ocfs2_cow_context *context = शून्य;
	u32 cow_start, cow_len;

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_refcount_cal_cow_clusters(inode, &xv->xr_list,
					      cpos, ग_लिखो_len, अच_पूर्णांक_उच्च,
					      &cow_start, &cow_len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	BUG_ON(cow_len == 0);

	context = kzalloc(माप(काष्ठा ocfs2_cow_context), GFP_NOFS);
	अगर (!context) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	context->inode = inode;
	context->cow_start = cow_start;
	context->cow_len = cow_len;
	context->ref_tree = ref_tree;
	context->ref_root_bh = ref_root_bh;
	context->cow_object = xv;

	context->cow_duplicate_clusters = ocfs2_duplicate_clusters_by_jbd;
	/* We need the extra credits क्रम duplicate_clusters by jbd. */
	context->extra_credits =
		ocfs2_clusters_to_blocks(inode->i_sb, 1) * cow_len;
	context->get_clusters = ocfs2_xattr_value_get_clusters;
	context->post_refcount = post;

	ocfs2_init_xattr_value_extent_tree(&context->data_et,
					   INODE_CACHE(inode), vb);

	ret = ocfs2_replace_cow(context);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out:
	kमुक्त(context);
	वापस ret;
पूर्ण

/*
 * Insert a new extent पूर्णांकo refcount tree and mark a extent rec
 * as refcounted in the dinode tree.
 */
पूर्णांक ocfs2_add_refcount_flag(काष्ठा inode *inode,
			    काष्ठा ocfs2_extent_tree *data_et,
			    काष्ठा ocfs2_caching_info *ref_ci,
			    काष्ठा buffer_head *ref_root_bh,
			    u32 cpos, u32 p_cluster, u32 num_clusters,
			    काष्ठा ocfs2_cached_dealloc_ctxt *dealloc,
			    काष्ठा ocfs2_post_refcount *post)
अणु
	पूर्णांक ret;
	handle_t *handle;
	पूर्णांक credits = 1, ref_blocks = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;

	/* We need to be able to handle at least an extent tree split. */
	ref_blocks = ocfs2_extend_meta_needed(data_et->et_root_el);

	ret = ocfs2_calc_refcount_meta_credits(inode->i_sb,
					       ref_ci, ref_root_bh,
					       p_cluster, num_clusters,
					       &ref_blocks, &credits);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_add_refcount_flag(ref_blocks, credits);

	अगर (ref_blocks) अणु
		ret = ocfs2_reserve_new_metadata_blocks(osb,
							ref_blocks, &meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (post)
		credits += post->credits;

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_mark_extent_refcounted(inode, data_et, handle,
					   cpos, num_clusters, p_cluster,
					   meta_ac, dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = __ocfs2_increase_refcount(handle, ref_ci, ref_root_bh,
					p_cluster, num_clusters, 0,
					meta_ac, dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	अगर (post && post->func) अणु
		ret = post->func(inode, handle, post->para);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_change_स_समय(काष्ठा inode *inode,
			      काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	handle = ocfs2_start_trans(OCFS2_SB(inode->i_sb),
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

	inode->i_स_समय = current_समय(inode);
	di->i_स_समय = cpu_to_le64(inode->i_स_समय.tv_sec);
	di->i_स_समय_nsec = cpu_to_le32(inode->i_स_समय.tv_nsec);

	ocfs2_journal_dirty(handle, di_bh);

out_commit:
	ocfs2_commit_trans(OCFS2_SB(inode->i_sb), handle);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_attach_refcount_tree(काष्ठा inode *inode,
				      काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret, data_changed = 0;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(inode);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_refcount_tree *ref_tree;
	अचिन्हित पूर्णांक ext_flags;
	loff_t size;
	u32 cpos, num_clusters, clusters, p_cluster;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_extent_tree di_et;

	ocfs2_init_dealloc_ctxt(&dealloc);

	अगर (!ocfs2_is_refcount_inode(inode)) अणु
		ret = ocfs2_create_refcount_tree(inode, di_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	BUG_ON(!di->i_refcount_loc);
	ret = ocfs2_lock_refcount_tree(osb,
				       le64_to_cpu(di->i_refcount_loc), 1,
				       &ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		जाओ attach_xattr;

	ocfs2_init_dinode_extent_tree(&di_et, INODE_CACHE(inode), di_bh);

	size = i_size_पढ़ो(inode);
	clusters = ocfs2_clusters_क्रम_bytes(inode->i_sb, size);

	cpos = 0;
	जबतक (cpos < clusters) अणु
		ret = ocfs2_get_clusters(inode, cpos, &p_cluster,
					 &num_clusters, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ unlock;
		पूर्ण
		अगर (p_cluster && !(ext_flags & OCFS2_EXT_REFCOUNTED)) अणु
			ret = ocfs2_add_refcount_flag(inode, &di_et,
						      &ref_tree->rf_ci,
						      ref_root_bh, cpos,
						      p_cluster, num_clusters,
						      &dealloc, शून्य);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ unlock;
			पूर्ण

			data_changed = 1;
		पूर्ण
		cpos += num_clusters;
	पूर्ण

attach_xattr:
	अगर (oi->ip_dyn_features & OCFS2_HAS_XATTR_FL) अणु
		ret = ocfs2_xattr_attach_refcount_tree(inode, di_bh,
						       &ref_tree->rf_ci,
						       ref_root_bh,
						       &dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ unlock;
		पूर्ण
	पूर्ण

	अगर (data_changed) अणु
		ret = ocfs2_change_स_समय(inode, di_bh);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण

unlock:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brअन्यथा(ref_root_bh);

	अगर (!ret && ocfs2_dealloc_has_cluster(&dealloc)) अणु
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &dealloc);
	पूर्ण
out:
	/*
	 * Empty the extent map so that we may get the right extent
	 * record from the disk.
	 */
	ocfs2_extent_map_trunc(inode, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_add_refcounted_extent(काष्ठा inode *inode,
				   काष्ठा ocfs2_extent_tree *et,
				   काष्ठा ocfs2_caching_info *ref_ci,
				   काष्ठा buffer_head *ref_root_bh,
				   u32 cpos, u32 p_cluster, u32 num_clusters,
				   अचिन्हित पूर्णांक ext_flags,
				   काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret;
	handle_t *handle;
	पूर्णांक credits = 0;
	काष्ठा ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;

	ret = ocfs2_lock_refcount_allocators(inode->i_sb,
					     p_cluster, num_clusters,
					     et, ref_ci,
					     ref_root_bh, &meta_ac,
					     शून्य, &credits);
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

	ret = ocfs2_insert_extent(handle, et, cpos,
			ocfs2_clusters_to_blocks(inode->i_sb, p_cluster),
			num_clusters, ext_flags, meta_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = ocfs2_increase_refcount(handle, ref_ci, ref_root_bh,
				      p_cluster, num_clusters,
				      meta_ac, dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = dquot_alloc_space_nodirty(inode,
		ocfs2_clusters_to_bytes(osb->sb, num_clusters));
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_duplicate_अंतरभूत_data(काष्ठा inode *s_inode,
				       काष्ठा buffer_head *s_bh,
				       काष्ठा inode *t_inode,
				       काष्ठा buffer_head *t_bh)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा ocfs2_super *osb = OCFS2_SB(s_inode->i_sb);
	काष्ठा ocfs2_dinode *s_di = (काष्ठा ocfs2_dinode *)s_bh->b_data;
	काष्ठा ocfs2_dinode *t_di = (काष्ठा ocfs2_dinode *)t_bh->b_data;

	BUG_ON(!(OCFS2_I(s_inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL));

	handle = ocfs2_start_trans(osb, OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(t_inode), t_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	t_di->id2.i_data.id_count = s_di->id2.i_data.id_count;
	स_नकल(t_di->id2.i_data.id_data, s_di->id2.i_data.id_data,
	       le16_to_cpu(s_di->id2.i_data.id_count));
	spin_lock(&OCFS2_I(t_inode)->ip_lock);
	OCFS2_I(t_inode)->ip_dyn_features |= OCFS2_INLINE_DATA_FL;
	t_di->i_dyn_features = cpu_to_le16(OCFS2_I(t_inode)->ip_dyn_features);
	spin_unlock(&OCFS2_I(t_inode)->ip_lock);

	ocfs2_journal_dirty(handle, t_bh);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_duplicate_extent_list(काष्ठा inode *s_inode,
				काष्ठा inode *t_inode,
				काष्ठा buffer_head *t_bh,
				काष्ठा ocfs2_caching_info *ref_ci,
				काष्ठा buffer_head *ref_root_bh,
				काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	पूर्णांक ret = 0;
	u32 p_cluster, num_clusters, clusters, cpos;
	loff_t size;
	अचिन्हित पूर्णांक ext_flags;
	काष्ठा ocfs2_extent_tree et;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(t_inode), t_bh);

	size = i_size_पढ़ो(s_inode);
	clusters = ocfs2_clusters_क्रम_bytes(s_inode->i_sb, size);

	cpos = 0;
	जबतक (cpos < clusters) अणु
		ret = ocfs2_get_clusters(s_inode, cpos, &p_cluster,
					 &num_clusters, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
		अगर (p_cluster) अणु
			ret = ocfs2_add_refcounted_extent(t_inode, &et,
							  ref_ci, ref_root_bh,
							  cpos, p_cluster,
							  num_clusters,
							  ext_flags,
							  dealloc);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

		cpos += num_clusters;
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * change the new file's attributes to the src.
 *
 * reflink creates a snapshot of a file, that means the attributes
 * must be identical except क्रम three exceptions - nlink, ino, and स_समय.
 */
अटल पूर्णांक ocfs2_complete_reflink(काष्ठा inode *s_inode,
				  काष्ठा buffer_head *s_bh,
				  काष्ठा inode *t_inode,
				  काष्ठा buffer_head *t_bh,
				  bool preserve)
अणु
	पूर्णांक ret;
	handle_t *handle;
	काष्ठा ocfs2_dinode *s_di = (काष्ठा ocfs2_dinode *)s_bh->b_data;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)t_bh->b_data;
	loff_t size = i_size_पढ़ो(s_inode);

	handle = ocfs2_start_trans(OCFS2_SB(t_inode->i_sb),
				   OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(t_inode), t_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	spin_lock(&OCFS2_I(t_inode)->ip_lock);
	OCFS2_I(t_inode)->ip_clusters = OCFS2_I(s_inode)->ip_clusters;
	OCFS2_I(t_inode)->ip_attr = OCFS2_I(s_inode)->ip_attr;
	OCFS2_I(t_inode)->ip_dyn_features = OCFS2_I(s_inode)->ip_dyn_features;
	spin_unlock(&OCFS2_I(t_inode)->ip_lock);
	i_size_ग_लिखो(t_inode, size);
	t_inode->i_blocks = s_inode->i_blocks;

	di->i_xattr_अंतरभूत_size = s_di->i_xattr_अंतरभूत_size;
	di->i_clusters = s_di->i_clusters;
	di->i_size = s_di->i_size;
	di->i_dyn_features = s_di->i_dyn_features;
	di->i_attr = s_di->i_attr;

	अगर (preserve) अणु
		t_inode->i_uid = s_inode->i_uid;
		t_inode->i_gid = s_inode->i_gid;
		t_inode->i_mode = s_inode->i_mode;
		di->i_uid = s_di->i_uid;
		di->i_gid = s_di->i_gid;
		di->i_mode = s_di->i_mode;

		/*
		 * update समय.
		 * we want mसमय to appear identical to the source and
		 * update स_समय.
		 */
		t_inode->i_स_समय = current_समय(t_inode);

		di->i_स_समय = cpu_to_le64(t_inode->i_स_समय.tv_sec);
		di->i_स_समय_nsec = cpu_to_le32(t_inode->i_स_समय.tv_nsec);

		t_inode->i_mसमय = s_inode->i_mसमय;
		di->i_mसमय = s_di->i_mसमय;
		di->i_mसमय_nsec = s_di->i_mसमय_nsec;
	पूर्ण

	ocfs2_journal_dirty(handle, t_bh);

out_commit:
	ocfs2_commit_trans(OCFS2_SB(t_inode->i_sb), handle);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_create_reflink_node(काष्ठा inode *s_inode,
				     काष्ठा buffer_head *s_bh,
				     काष्ठा inode *t_inode,
				     काष्ठा buffer_head *t_bh,
				     bool preserve)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_super *osb = OCFS2_SB(s_inode->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)s_bh->b_data;
	काष्ठा ocfs2_refcount_tree *ref_tree;

	ocfs2_init_dealloc_ctxt(&dealloc);

	ret = ocfs2_set_refcount_tree(t_inode, t_bh,
				      le64_to_cpu(di->i_refcount_loc));
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (OCFS2_I(s_inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = ocfs2_duplicate_अंतरभूत_data(s_inode, s_bh,
						  t_inode, t_bh);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_lock_refcount_tree(osb, le64_to_cpu(di->i_refcount_loc),
				       1, &ref_tree, &ref_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_duplicate_extent_list(s_inode, t_inode, t_bh,
					  &ref_tree->rf_ci, ref_root_bh,
					  &dealloc);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock_refcount;
	पूर्ण

out_unlock_refcount:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brअन्यथा(ref_root_bh);
out:
	अगर (ocfs2_dealloc_has_cluster(&dealloc)) अणु
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &dealloc);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __ocfs2_reflink(काष्ठा dentry *old_dentry,
			   काष्ठा buffer_head *old_bh,
			   काष्ठा inode *new_inode,
			   bool preserve)
अणु
	पूर्णांक ret;
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा buffer_head *new_bh = शून्य;

	अगर (OCFS2_I(inode)->ip_flags & OCFS2_INODE_SYSTEM_खाता) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = filemap_fdataग_लिखो(inode->i_mapping);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_attach_refcount_tree(inode, old_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	inode_lock_nested(new_inode, I_MUTEX_CHILD);
	ret = ocfs2_inode_lock_nested(new_inode, &new_bh, 1,
				      OI_LS_REFLINK_TARGET);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_create_reflink_node(inode, old_bh,
					new_inode, new_bh, preserve);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ inode_unlock;
	पूर्ण

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_HAS_XATTR_FL) अणु
		ret = ocfs2_reflink_xattrs(inode, old_bh,
					   new_inode, new_bh,
					   preserve);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ inode_unlock;
		पूर्ण
	पूर्ण

	ret = ocfs2_complete_reflink(inode, old_bh,
				     new_inode, new_bh, preserve);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

inode_unlock:
	ocfs2_inode_unlock(new_inode, 1);
	brअन्यथा(new_bh);
out_unlock:
	inode_unlock(new_inode);
out:
	अगर (!ret) अणु
		ret = filemap_fdataरुको(inode->i_mapping);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_reflink(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			 काष्ठा dentry *new_dentry, bool preserve)
अणु
	पूर्णांक error, had_lock;
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा buffer_head *old_bh = शून्य;
	काष्ठा inode *new_orphan_inode = शून्य;
	काष्ठा ocfs2_lock_holder oh;

	अगर (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)))
		वापस -EOPNOTSUPP;


	error = ocfs2_create_inode_in_orphan(dir, inode->i_mode,
					     &new_orphan_inode);
	अगर (error) अणु
		mlog_त्रुटि_सं(error);
		जाओ out;
	पूर्ण

	error = ocfs2_rw_lock(inode, 1);
	अगर (error) अणु
		mlog_त्रुटि_सं(error);
		जाओ out;
	पूर्ण

	error = ocfs2_inode_lock(inode, &old_bh, 1);
	अगर (error) अणु
		mlog_त्रुटि_सं(error);
		ocfs2_rw_unlock(inode, 1);
		जाओ out;
	पूर्ण

	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);
	करोwn_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	error = __ocfs2_reflink(old_dentry, old_bh,
				new_orphan_inode, preserve);
	up_ग_लिखो(&OCFS2_I(inode)->ip_alloc_sem);
	up_ग_लिखो(&OCFS2_I(inode)->ip_xattr_sem);

	ocfs2_inode_unlock(inode, 1);
	ocfs2_rw_unlock(inode, 1);
	brअन्यथा(old_bh);

	अगर (error) अणु
		mlog_त्रुटि_सं(error);
		जाओ out;
	पूर्ण

	had_lock = ocfs2_inode_lock_tracker(new_orphan_inode, शून्य, 1,
					    &oh);
	अगर (had_lock < 0) अणु
		error = had_lock;
		mlog_त्रुटि_सं(error);
		जाओ out;
	पूर्ण

	/* If the security isn't preserved, we need to re-initialize them. */
	अगर (!preserve) अणु
		error = ocfs2_init_security_and_acl(dir, new_orphan_inode,
						    &new_dentry->d_name);
		अगर (error)
			mlog_त्रुटि_सं(error);
	पूर्ण
	अगर (!error) अणु
		error = ocfs2_mv_orphaned_inode_to_new(dir, new_orphan_inode,
						       new_dentry);
		अगर (error)
			mlog_त्रुटि_सं(error);
	पूर्ण
	ocfs2_inode_unlock_tracker(new_orphan_inode, 1, &oh, had_lock);

out:
	अगर (new_orphan_inode) अणु
		/*
		 * We need to खोलो_unlock the inode no matter whether we
		 * succeed or not, so that other nodes can delete it later.
		 */
		ocfs2_खोलो_unlock(new_orphan_inode);
		अगर (error)
			iput(new_orphan_inode);
	पूर्ण

	वापस error;
पूर्ण

/*
 * Below here are the bits used by OCFS2_IOC_REFLINK() to fake
 * sys_reflink().  This will go away when vfs_reflink() exists in
 * fs/namei.c.
 */

/* copied from may_create in VFS. */
अटल अंतरभूत पूर्णांक ocfs2_may_create(काष्ठा inode *dir, काष्ठा dentry *child)
अणु
	अगर (d_really_is_positive(child))
		वापस -EEXIST;
	अगर (IS_DEADसूची(dir))
		वापस -ENOENT;
	वापस inode_permission(&init_user_ns, dir, MAY_WRITE | MAY_EXEC);
पूर्ण

/**
 * ocfs2_vfs_reflink - Create a reference-counted link
 *
 * @old_dentry:        source dentry + inode
 * @dir:       directory to create the target
 * @new_dentry:        target dentry
 * @preserve:  अगर true, preserve all file attributes
 */
अटल पूर्णांक ocfs2_vfs_reflink(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
			     काष्ठा dentry *new_dentry, bool preserve)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	पूर्णांक error;

	अगर (!inode)
		वापस -ENOENT;

	error = ocfs2_may_create(dir, new_dentry);
	अगर (error)
		वापस error;

	अगर (dir->i_sb != inode->i_sb)
		वापस -EXDEV;

	/*
	 * A reflink to an append-only or immutable file cannot be created.
	 */
	अगर (IS_APPEND(inode) || IS_IMMUTABLE(inode))
		वापस -EPERM;

	/* Only regular files can be reflinked. */
	अगर (!S_ISREG(inode->i_mode))
		वापस -EPERM;

	/*
	 * If the caller wants to preserve ownership, they require the
	 * rights to करो so.
	 */
	अगर (preserve) अणु
		अगर (!uid_eq(current_fsuid(), inode->i_uid) && !capable(CAP_CHOWN))
			वापस -EPERM;
		अगर (!in_group_p(inode->i_gid) && !capable(CAP_CHOWN))
			वापस -EPERM;
	पूर्ण

	/*
	 * If the caller is modअगरying any aspect of the attributes, they
	 * are not creating a snapshot.  They need पढ़ो permission on the
	 * file.
	 */
	अगर (!preserve) अणु
		error = inode_permission(&init_user_ns, inode, MAY_READ);
		अगर (error)
			वापस error;
	पूर्ण

	inode_lock(inode);
	error = dquot_initialize(dir);
	अगर (!error)
		error = ocfs2_reflink(old_dentry, dir, new_dentry, preserve);
	inode_unlock(inode);
	अगर (!error)
		fsnotअगरy_create(dir, new_dentry);
	वापस error;
पूर्ण
/*
 * Most codes are copied from sys_linkat.
 */
पूर्णांक ocfs2_reflink_ioctl(काष्ठा inode *inode,
			स्थिर अक्षर __user *oldname,
			स्थिर अक्षर __user *newname,
			bool preserve)
अणु
	काष्ठा dentry *new_dentry;
	काष्ठा path old_path, new_path;
	पूर्णांक error;

	अगर (!ocfs2_refcount_tree(OCFS2_SB(inode->i_sb)))
		वापस -EOPNOTSUPP;

	error = user_path_at(AT_FDCWD, oldname, 0, &old_path);
	अगर (error) अणु
		mlog_त्रुटि_सं(error);
		वापस error;
	पूर्ण

	new_dentry = user_path_create(AT_FDCWD, newname, &new_path, 0);
	error = PTR_ERR(new_dentry);
	अगर (IS_ERR(new_dentry)) अणु
		mlog_त्रुटि_सं(error);
		जाओ out;
	पूर्ण

	error = -EXDEV;
	अगर (old_path.mnt != new_path.mnt) अणु
		mlog_त्रुटि_सं(error);
		जाओ out_dput;
	पूर्ण

	error = ocfs2_vfs_reflink(old_path.dentry,
				  d_inode(new_path.dentry),
				  new_dentry, preserve);
out_dput:
	करोne_path_create(&new_path, new_dentry);
out:
	path_put(&old_path);

	वापस error;
पूर्ण

/* Update destination inode size, अगर necessary. */
पूर्णांक ocfs2_reflink_update_dest(काष्ठा inode *dest,
			      काष्ठा buffer_head *d_bh,
			      loff_t newlen)
अणु
	handle_t *handle;
	पूर्णांक ret;

	dest->i_blocks = ocfs2_inode_sector_count(dest);

	अगर (newlen <= i_size_पढ़ो(dest))
		वापस 0;

	handle = ocfs2_start_trans(OCFS2_SB(dest->i_sb),
				   OCFS2_INODE_UPDATE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		वापस ret;
	पूर्ण

	/* Extend i_size अगर needed. */
	spin_lock(&OCFS2_I(dest)->ip_lock);
	अगर (newlen > i_size_पढ़ो(dest))
		i_size_ग_लिखो(dest, newlen);
	spin_unlock(&OCFS2_I(dest)->ip_lock);
	dest->i_स_समय = dest->i_mसमय = current_समय(dest);

	ret = ocfs2_mark_inode_dirty(handle, dest, d_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

out_commit:
	ocfs2_commit_trans(OCFS2_SB(dest->i_sb), handle);
	वापस ret;
पूर्ण

/* Remap the range pos_in:len in s_inode to pos_out:len in t_inode. */
अटल loff_t ocfs2_reflink_remap_extent(काष्ठा inode *s_inode,
					 काष्ठा buffer_head *s_bh,
					 loff_t pos_in,
					 काष्ठा inode *t_inode,
					 काष्ठा buffer_head *t_bh,
					 loff_t pos_out,
					 loff_t len,
					 काष्ठा ocfs2_cached_dealloc_ctxt *dealloc)
अणु
	काष्ठा ocfs2_extent_tree s_et;
	काष्ठा ocfs2_extent_tree t_et;
	काष्ठा ocfs2_dinode *dis;
	काष्ठा buffer_head *ref_root_bh = शून्य;
	काष्ठा ocfs2_refcount_tree *ref_tree;
	काष्ठा ocfs2_super *osb;
	loff_t remapped_bytes = 0;
	loff_t pstart, plen;
	u32 p_cluster, num_clusters, slast, spos, tpos, remapped_clus = 0;
	अचिन्हित पूर्णांक ext_flags;
	पूर्णांक ret = 0;

	osb = OCFS2_SB(s_inode->i_sb);
	dis = (काष्ठा ocfs2_dinode *)s_bh->b_data;
	ocfs2_init_dinode_extent_tree(&s_et, INODE_CACHE(s_inode), s_bh);
	ocfs2_init_dinode_extent_tree(&t_et, INODE_CACHE(t_inode), t_bh);

	spos = ocfs2_bytes_to_clusters(s_inode->i_sb, pos_in);
	tpos = ocfs2_bytes_to_clusters(t_inode->i_sb, pos_out);
	slast = ocfs2_clusters_क्रम_bytes(s_inode->i_sb, pos_in + len);

	जबतक (spos < slast) अणु
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			जाओ out;
		पूर्ण

		/* Look up the extent. */
		ret = ocfs2_get_clusters(s_inode, spos, &p_cluster,
					 &num_clusters, &ext_flags);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		num_clusters = min_t(u32, num_clusters, slast - spos);

		/* Punch out the dest range. */
		pstart = ocfs2_clusters_to_bytes(t_inode->i_sb, tpos);
		plen = ocfs2_clusters_to_bytes(t_inode->i_sb, num_clusters);
		ret = ocfs2_हटाओ_inode_range(t_inode, t_bh, pstart, plen);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (p_cluster == 0)
			जाओ next_loop;

		/* Lock the refcount btree... */
		ret = ocfs2_lock_refcount_tree(osb,
					       le64_to_cpu(dis->i_refcount_loc),
					       1, &ref_tree, &ref_root_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/* Mark s_inode's extent as refcounted. */
		अगर (!(ext_flags & OCFS2_EXT_REFCOUNTED)) अणु
			ret = ocfs2_add_refcount_flag(s_inode, &s_et,
						      &ref_tree->rf_ci,
						      ref_root_bh, spos,
						      p_cluster, num_clusters,
						      dealloc, शून्य);
			अगर (ret) अणु
				mlog_त्रुटि_सं(ret);
				जाओ out_unlock_refcount;
			पूर्ण
		पूर्ण

		/* Map in the new extent. */
		ext_flags |= OCFS2_EXT_REFCOUNTED;
		ret = ocfs2_add_refcounted_extent(t_inode, &t_et,
						  &ref_tree->rf_ci,
						  ref_root_bh,
						  tpos, p_cluster,
						  num_clusters,
						  ext_flags,
						  dealloc);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_unlock_refcount;
		पूर्ण

		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
		brअन्यथा(ref_root_bh);
next_loop:
		spos += num_clusters;
		tpos += num_clusters;
		remapped_clus += num_clusters;
	पूर्ण

	जाओ out;
out_unlock_refcount:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brअन्यथा(ref_root_bh);
out:
	remapped_bytes = ocfs2_clusters_to_bytes(t_inode->i_sb, remapped_clus);
	remapped_bytes = min_t(loff_t, len, remapped_bytes);

	वापस remapped_bytes > 0 ? remapped_bytes : ret;
पूर्ण

/* Set up refcount tree and remap s_inode to t_inode. */
loff_t ocfs2_reflink_remap_blocks(काष्ठा inode *s_inode,
				  काष्ठा buffer_head *s_bh,
				  loff_t pos_in,
				  काष्ठा inode *t_inode,
				  काष्ठा buffer_head *t_bh,
				  loff_t pos_out,
				  loff_t len)
अणु
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_super *osb;
	काष्ठा ocfs2_dinode *dis;
	काष्ठा ocfs2_dinode *dit;
	loff_t ret;

	osb = OCFS2_SB(s_inode->i_sb);
	dis = (काष्ठा ocfs2_dinode *)s_bh->b_data;
	dit = (काष्ठा ocfs2_dinode *)t_bh->b_data;
	ocfs2_init_dealloc_ctxt(&dealloc);

	/*
	 * If we're reflinking the entire file and the source is अंतरभूत
	 * data, just copy the contents.
	 */
	अगर (pos_in == pos_out && pos_in == 0 && len == i_size_पढ़ो(s_inode) &&
	    i_size_पढ़ो(t_inode) <= len &&
	    (OCFS2_I(s_inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)) अणु
		ret = ocfs2_duplicate_अंतरभूत_data(s_inode, s_bh, t_inode, t_bh);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * If both inodes beदीर्घ to two dअगरferent refcount groups then
	 * क्रमget it because we करोn't know how (or want) to go merging
	 * refcount trees.
	 */
	ret = -EOPNOTSUPP;
	अगर (ocfs2_is_refcount_inode(s_inode) &&
	    ocfs2_is_refcount_inode(t_inode) &&
	    le64_to_cpu(dis->i_refcount_loc) !=
	    le64_to_cpu(dit->i_refcount_loc))
		जाओ out;

	/* Neither inode has a refcount tree.  Add one to s_inode. */
	अगर (!ocfs2_is_refcount_inode(s_inode) &&
	    !ocfs2_is_refcount_inode(t_inode)) अणु
		ret = ocfs2_create_refcount_tree(s_inode, s_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Ensure that both inodes end up with the same refcount tree. */
	अगर (!ocfs2_is_refcount_inode(s_inode)) अणु
		ret = ocfs2_set_refcount_tree(s_inode, s_bh,
					      le64_to_cpu(dit->i_refcount_loc));
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (!ocfs2_is_refcount_inode(t_inode)) अणु
		ret = ocfs2_set_refcount_tree(t_inode, t_bh,
					      le64_to_cpu(dis->i_refcount_loc));
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Turn off अंतरभूत data in the dest file. */
	अगर (OCFS2_I(t_inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = ocfs2_convert_अंतरभूत_data_to_extents(t_inode, t_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/* Actually remap extents now. */
	ret = ocfs2_reflink_remap_extent(s_inode, s_bh, pos_in, t_inode, t_bh,
					 pos_out, len, &dealloc);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

out:
	अगर (ocfs2_dealloc_has_cluster(&dealloc)) अणु
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &dealloc);
	पूर्ण

	वापस ret;
पूर्ण

/* Lock an inode and grab a bh poपूर्णांकing to the inode. */
पूर्णांक ocfs2_reflink_inodes_lock(काष्ठा inode *s_inode,
			      काष्ठा buffer_head **bh_s,
			      काष्ठा inode *t_inode,
			      काष्ठा buffer_head **bh_t)
अणु
	काष्ठा inode *inode1 = s_inode;
	काष्ठा inode *inode2 = t_inode;
	काष्ठा ocfs2_inode_info *oi1;
	काष्ठा ocfs2_inode_info *oi2;
	काष्ठा buffer_head *bh1 = शून्य;
	काष्ठा buffer_head *bh2 = शून्य;
	bool same_inode = (s_inode == t_inode);
	bool need_swap = (inode1->i_ino > inode2->i_ino);
	पूर्णांक status;

	/* First grab the VFS and rw locks. */
	lock_two_nondirectories(s_inode, t_inode);
	अगर (need_swap)
		swap(inode1, inode2);

	status = ocfs2_rw_lock(inode1, 1);
	अगर (status) अणु
		mlog_त्रुटि_सं(status);
		जाओ out_i1;
	पूर्ण
	अगर (!same_inode) अणु
		status = ocfs2_rw_lock(inode2, 1);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ out_i2;
		पूर्ण
	पूर्ण

	/* Now go क्रम the cluster locks */
	oi1 = OCFS2_I(inode1);
	oi2 = OCFS2_I(inode2);

	trace_ocfs2_द्विगुन_lock((अचिन्हित दीर्घ दीर्घ)oi1->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)oi2->ip_blkno);

	/* We always want to lock the one with the lower lockid first. */
	अगर (oi1->ip_blkno > oi2->ip_blkno)
		mlog_त्रुटि_सं(-ENOLCK);

	/* lock id1 */
	status = ocfs2_inode_lock_nested(inode1, &bh1, 1,
					 OI_LS_REFLINK_TARGET);
	अगर (status < 0) अणु
		अगर (status != -ENOENT)
			mlog_त्रुटि_सं(status);
		जाओ out_rw2;
	पूर्ण

	/* lock id2 */
	अगर (!same_inode) अणु
		status = ocfs2_inode_lock_nested(inode2, &bh2, 1,
						 OI_LS_REFLINK_TARGET);
		अगर (status < 0) अणु
			अगर (status != -ENOENT)
				mlog_त्रुटि_सं(status);
			जाओ out_cl1;
		पूर्ण
	पूर्ण अन्यथा अणु
		bh2 = bh1;
	पूर्ण

	/*
	 * If we swapped inode order above, we have to swap the buffer heads
	 * beक्रमe passing them back to the caller.
	 */
	अगर (need_swap)
		swap(bh1, bh2);
	*bh_s = bh1;
	*bh_t = bh2;

	trace_ocfs2_द्विगुन_lock_end(
			(अचिन्हित दीर्घ दीर्घ)oi1->ip_blkno,
			(अचिन्हित दीर्घ दीर्घ)oi2->ip_blkno);

	वापस 0;

out_cl1:
	ocfs2_inode_unlock(inode1, 1);
	brअन्यथा(bh1);
out_rw2:
	ocfs2_rw_unlock(inode2, 1);
out_i2:
	ocfs2_rw_unlock(inode1, 1);
out_i1:
	unlock_two_nondirectories(s_inode, t_inode);
	वापस status;
पूर्ण

/* Unlock both inodes and release buffers. */
व्योम ocfs2_reflink_inodes_unlock(काष्ठा inode *s_inode,
				 काष्ठा buffer_head *s_bh,
				 काष्ठा inode *t_inode,
				 काष्ठा buffer_head *t_bh)
अणु
	ocfs2_inode_unlock(s_inode, 1);
	ocfs2_rw_unlock(s_inode, 1);
	brअन्यथा(s_bh);
	अगर (s_inode != t_inode) अणु
		ocfs2_inode_unlock(t_inode, 1);
		ocfs2_rw_unlock(t_inode, 1);
		brअन्यथा(t_bh);
	पूर्ण
	unlock_two_nondirectories(s_inode, t_inode);
पूर्ण
