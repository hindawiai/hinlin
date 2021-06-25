<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * index.c - NTFS kernel index handling.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2004-2005 Anton Altaparmakov
 */

#समावेश <linux/slab.h>

#समावेश "aops.h"
#समावेश "collate.h"
#समावेश "debug.h"
#समावेश "index.h"
#समावेश "ntfs.h"

/**
 * ntfs_index_ctx_get - allocate and initialize a new index context
 * @idx_ni:	ntfs index inode with which to initialize the context
 *
 * Allocate a new index context, initialize it with @idx_ni and वापस it.
 * Return शून्य अगर allocation failed.
 *
 * Locking:  Caller must hold i_mutex on the index inode.
 */
ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *idx_ni)
अणु
	ntfs_index_context *ictx;

	ictx = kmem_cache_alloc(ntfs_index_ctx_cache, GFP_NOFS);
	अगर (ictx)
		*ictx = (ntfs_index_context)अणु .idx_ni = idx_ni पूर्ण;
	वापस ictx;
पूर्ण

/**
 * ntfs_index_ctx_put - release an index context
 * @ictx:	index context to मुक्त
 *
 * Release the index context @ictx, releasing all associated resources.
 *
 * Locking:  Caller must hold i_mutex on the index inode.
 */
व्योम ntfs_index_ctx_put(ntfs_index_context *ictx)
अणु
	अगर (ictx->entry) अणु
		अगर (ictx->is_in_root) अणु
			अगर (ictx->actx)
				ntfs_attr_put_search_ctx(ictx->actx);
			अगर (ictx->base_ni)
				unmap_mft_record(ictx->base_ni);
		पूर्ण अन्यथा अणु
			काष्ठा page *page = ictx->page;
			अगर (page) अणु
				BUG_ON(!PageLocked(page));
				unlock_page(page);
				ntfs_unmap_page(page);
			पूर्ण
		पूर्ण
	पूर्ण
	kmem_cache_मुक्त(ntfs_index_ctx_cache, ictx);
	वापस;
पूर्ण

/**
 * ntfs_index_lookup - find a key in an index and वापस its index entry
 * @key:	[IN] key क्रम which to search in the index
 * @key_len:	[IN] length of @key in bytes
 * @ictx:	[IN/OUT] context describing the index and the वापसed entry
 *
 * Beक्रमe calling ntfs_index_lookup(), @ictx must have been obtained from a
 * call to ntfs_index_ctx_get().
 *
 * Look क्रम the @key in the index specअगरied by the index lookup context @ictx.
 * ntfs_index_lookup() walks the contents of the index looking क्रम the @key.
 *
 * If the @key is found in the index, 0 is वापसed and @ictx is setup to
 * describe the index entry containing the matching @key.  @ictx->entry is the
 * index entry and @ictx->data and @ictx->data_len are the index entry data and
 * its length in bytes, respectively.
 *
 * If the @key is not found in the index, -ENOENT is वापसed and @ictx is
 * setup to describe the index entry whose key collates immediately after the
 * search @key, i.e. this is the position in the index at which an index entry
 * with a key of @key would need to be inserted.
 *
 * If an error occurs वापस the negative error code and @ictx is left
 * untouched.
 *
 * When finished with the entry and its data, call ntfs_index_ctx_put() to मुक्त
 * the context and other associated resources.
 *
 * If the index entry was modअगरied, call flush_dcache_index_entry_page()
 * immediately after the modअगरication and either ntfs_index_entry_mark_dirty()
 * or ntfs_index_entry_ग_लिखो() beक्रमe the call to ntfs_index_ctx_put() to
 * ensure that the changes are written to disk.
 *
 * Locking:  - Caller must hold i_mutex on the index inode.
 *	     - Each page cache page in the index allocation mapping must be
 *	       locked whilst being accessed otherwise we may find a corrupt
 *	       page due to it being under ->ग_लिखोpage at the moment which
 *	       applies the mst protection fixups beक्रमe writing out and then
 *	       हटाओs them again after the ग_लिखो is complete after which it 
 *	       unlocks the page.
 */
पूर्णांक ntfs_index_lookup(स्थिर व्योम *key, स्थिर पूर्णांक key_len,
		ntfs_index_context *ictx)
अणु
	VCN vcn, old_vcn;
	ntfs_inode *idx_ni = ictx->idx_ni;
	ntfs_volume *vol = idx_ni->vol;
	काष्ठा super_block *sb = vol->sb;
	ntfs_inode *base_ni = idx_ni->ext.base_ntfs_ino;
	MFT_RECORD *m;
	INDEX_ROOT *ir;
	INDEX_ENTRY *ie;
	INDEX_ALLOCATION *ia;
	u8 *index_end, *kaddr;
	ntfs_attr_search_ctx *actx;
	काष्ठा address_space *ia_mapping;
	काष्ठा page *page;
	पूर्णांक rc, err = 0;

	ntfs_debug("Entering.");
	BUG_ON(!NInoAttr(idx_ni));
	BUG_ON(idx_ni->type != AT_INDEX_ALLOCATION);
	BUG_ON(idx_ni->nr_extents != -1);
	BUG_ON(!base_ni);
	BUG_ON(!key);
	BUG_ON(key_len <= 0);
	अगर (!ntfs_is_collation_rule_supported(
			idx_ni->itype.index.collation_rule)) अणु
		ntfs_error(sb, "Index uses unsupported collation rule 0x%x.  "
				"Aborting lookup.", le32_to_cpu(
				idx_ni->itype.index.collation_rule));
		वापस -EOPNOTSUPP;
	पूर्ण
	/* Get hold of the mft record क्रम the index inode. */
	m = map_mft_record(base_ni);
	अगर (IS_ERR(m)) अणु
		ntfs_error(sb, "map_mft_record() failed with error code %ld.",
				-PTR_ERR(m));
		वापस PTR_ERR(m);
	पूर्ण
	actx = ntfs_attr_get_search_ctx(base_ni, m);
	अगर (unlikely(!actx)) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण
	/* Find the index root attribute in the mft record. */
	err = ntfs_attr_lookup(AT_INDEX_ROOT, idx_ni->name, idx_ni->name_len,
			CASE_SENSITIVE, 0, शून्य, 0, actx);
	अगर (unlikely(err)) अणु
		अगर (err == -ENOENT) अणु
			ntfs_error(sb, "Index root attribute missing in inode "
					"0x%lx.", idx_ni->mft_no);
			err = -EIO;
		पूर्ण
		जाओ err_out;
	पूर्ण
	/* Get to the index root value (it has been verअगरied in पढ़ो_inode). */
	ir = (INDEX_ROOT*)((u8*)actx->attr +
			le16_to_cpu(actx->attr->data.resident.value_offset));
	index_end = (u8*)&ir->index + le32_to_cpu(ir->index.index_length);
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ir->index +
			le32_to_cpu(ir->index.entries_offset));
	/*
	 * Loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds checks. */
		अगर ((u8*)ie < (u8*)actx->mrec || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->length) > index_end)
			जाओ idx_err_out;
		/*
		 * The last entry cannot contain a key.  It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/* Further bounds checks. */
		अगर ((u32)माप(INDEX_ENTRY_HEADER) +
				le16_to_cpu(ie->key_length) >
				le16_to_cpu(ie->data.vi.data_offset) ||
				(u32)le16_to_cpu(ie->data.vi.data_offset) +
				le16_to_cpu(ie->data.vi.data_length) >
				le16_to_cpu(ie->length))
			जाओ idx_err_out;
		/* If the keys match perfectly, we setup @ictx and वापस 0. */
		अगर ((key_len == le16_to_cpu(ie->key_length)) && !स_भेद(key,
				&ie->key, key_len)) अणु
ir_करोne:
			ictx->is_in_root = true;
			ictx->ir = ir;
			ictx->actx = actx;
			ictx->base_ni = base_ni;
			ictx->ia = शून्य;
			ictx->page = शून्य;
करोne:
			ictx->entry = ie;
			ictx->data = (u8*)ie +
					le16_to_cpu(ie->data.vi.data_offset);
			ictx->data_len = le16_to_cpu(ie->data.vi.data_length);
			ntfs_debug("Done.");
			वापस err;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate(vol, idx_ni->itype.index.collation_rule, key,
				key_len, &ie->key, le16_to_cpu(ie->key_length));
		/*
		 * If @key collates beक्रमe the key of the current entry, there
		 * is definitely no such key in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/*
		 * A match should never happen as the स_भेद() call should have
		 * cought it, but we still treat it correctly.
		 */
		अगर (!rc)
			जाओ ir_करोne;
		/* The keys are not equal, जारी the search. */
	पूर्ण
	/*
	 * We have finished with this index without success.  Check क्रम the
	 * presence of a child node and अगर not present setup @ictx and वापस
	 * -ENOENT.
	 */
	अगर (!(ie->flags & INDEX_ENTRY_NODE)) अणु
		ntfs_debug("Entry not found.");
		err = -ENOENT;
		जाओ ir_करोne;
	पूर्ण /* Child node present, descend पूर्णांकo it. */
	/* Consistency check: Verअगरy that an index allocation exists. */
	अगर (!NInoIndexAllocPresent(idx_ni)) अणु
		ntfs_error(sb, "No index allocation attribute but index entry "
				"requires one.  Inode 0x%lx is corrupt or "
				"driver bug.", idx_ni->mft_no);
		जाओ err_out;
	पूर्ण
	/* Get the starting vcn of the index_block holding the child node. */
	vcn = sle64_to_cpup((sle64*)((u8*)ie + le16_to_cpu(ie->length) - 8));
	ia_mapping = VFS_I(idx_ni)->i_mapping;
	/*
	 * We are करोne with the index root and the mft record.  Release them,
	 * otherwise we deadlock with ntfs_map_page().
	 */
	ntfs_attr_put_search_ctx(actx);
	unmap_mft_record(base_ni);
	m = शून्य;
	actx = शून्य;
descend_पूर्णांकo_child_node:
	/*
	 * Convert vcn to index पूर्णांकo the index allocation attribute in units
	 * of PAGE_SIZE and map the page cache page, पढ़ोing it from
	 * disk अगर necessary.
	 */
	page = ntfs_map_page(ia_mapping, vcn <<
			idx_ni->itype.index.vcn_size_bits >> PAGE_SHIFT);
	अगर (IS_ERR(page)) अणु
		ntfs_error(sb, "Failed to map index page, error %ld.",
				-PTR_ERR(page));
		err = PTR_ERR(page);
		जाओ err_out;
	पूर्ण
	lock_page(page);
	kaddr = (u8*)page_address(page);
fast_descend_पूर्णांकo_child_node:
	/* Get to the index allocation block. */
	ia = (INDEX_ALLOCATION*)(kaddr + ((vcn <<
			idx_ni->itype.index.vcn_size_bits) & ~PAGE_MASK));
	/* Bounds checks. */
	अगर ((u8*)ia < kaddr || (u8*)ia > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Out of bounds check failed.  Corrupt inode "
				"0x%lx or driver bug.", idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* Catch multi sector transfer fixup errors. */
	अगर (unlikely(!ntfs_is_indx_record(ia->magic))) अणु
		ntfs_error(sb, "Index record with vcn 0x%llx is corrupt.  "
				"Corrupt inode 0x%lx.  Run chkdsk.",
				(दीर्घ दीर्घ)vcn, idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (sle64_to_cpu(ia->index_block_vcn) != vcn) अणु
		ntfs_error(sb, "Actual VCN (0x%llx) of index buffer is "
				"different from expected VCN (0x%llx).  Inode "
				"0x%lx is corrupt or driver bug.",
				(अचिन्हित दीर्घ दीर्घ)
				sle64_to_cpu(ia->index_block_vcn),
				(अचिन्हित दीर्घ दीर्घ)vcn, idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	अगर (le32_to_cpu(ia->index.allocated_size) + 0x18 !=
			idx_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of inode 0x%lx has "
				"a size (%u) differing from the index "
				"specified size (%u).  Inode is corrupt or "
				"driver bug.", (अचिन्हित दीर्घ दीर्घ)vcn,
				idx_ni->mft_no,
				le32_to_cpu(ia->index.allocated_size) + 0x18,
				idx_ni->itype.index.block_size);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)ia + idx_ni->itype.index.block_size;
	अगर (index_end > kaddr + PAGE_SIZE) अणु
		ntfs_error(sb, "Index buffer (VCN 0x%llx) of inode 0x%lx "
				"crosses page boundary.  Impossible!  Cannot "
				"access!  This is probably a bug in the "
				"driver.", (अचिन्हित दीर्घ दीर्घ)vcn,
				idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	index_end = (u8*)&ia->index + le32_to_cpu(ia->index.index_length);
	अगर (index_end > (u8*)ia + idx_ni->itype.index.block_size) अणु
		ntfs_error(sb, "Size of index buffer (VCN 0x%llx) of inode "
				"0x%lx exceeds maximum size.",
				(अचिन्हित दीर्घ दीर्घ)vcn, idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* The first index entry. */
	ie = (INDEX_ENTRY*)((u8*)&ia->index +
			le32_to_cpu(ia->index.entries_offset));
	/*
	 * Iterate similar to above big loop but applied to index buffer, thus
	 * loop until we exceed valid memory (corruption हाल) or until we
	 * reach the last entry.
	 */
	क्रम (;; ie = (INDEX_ENTRY*)((u8*)ie + le16_to_cpu(ie->length))) अणु
		/* Bounds checks. */
		अगर ((u8*)ie < (u8*)ia || (u8*)ie +
				माप(INDEX_ENTRY_HEADER) > index_end ||
				(u8*)ie + le16_to_cpu(ie->length) > index_end) अणु
			ntfs_error(sb, "Index entry out of bounds in inode "
					"0x%lx.", idx_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/*
		 * The last entry cannot contain a key.  It can however contain
		 * a poपूर्णांकer to a child node in the B+tree so we just अवरोध out.
		 */
		अगर (ie->flags & INDEX_ENTRY_END)
			अवरोध;
		/* Further bounds checks. */
		अगर ((u32)माप(INDEX_ENTRY_HEADER) +
				le16_to_cpu(ie->key_length) >
				le16_to_cpu(ie->data.vi.data_offset) ||
				(u32)le16_to_cpu(ie->data.vi.data_offset) +
				le16_to_cpu(ie->data.vi.data_length) >
				le16_to_cpu(ie->length)) अणु
			ntfs_error(sb, "Index entry out of bounds in inode "
					"0x%lx.", idx_ni->mft_no);
			जाओ unm_err_out;
		पूर्ण
		/* If the keys match perfectly, we setup @ictx and वापस 0. */
		अगर ((key_len == le16_to_cpu(ie->key_length)) && !स_भेद(key,
				&ie->key, key_len)) अणु
ia_करोne:
			ictx->is_in_root = false;
			ictx->actx = शून्य;
			ictx->base_ni = शून्य;
			ictx->ia = ia;
			ictx->page = page;
			जाओ करोne;
		पूर्ण
		/*
		 * Not a perfect match, need to करो full blown collation so we
		 * know which way in the B+tree we have to go.
		 */
		rc = ntfs_collate(vol, idx_ni->itype.index.collation_rule, key,
				key_len, &ie->key, le16_to_cpu(ie->key_length));
		/*
		 * If @key collates beक्रमe the key of the current entry, there
		 * is definitely no such key in this index but we might need to
		 * descend पूर्णांकo the B+tree so we just अवरोध out of the loop.
		 */
		अगर (rc == -1)
			अवरोध;
		/*
		 * A match should never happen as the स_भेद() call should have
		 * cought it, but we still treat it correctly.
		 */
		अगर (!rc)
			जाओ ia_करोne;
		/* The keys are not equal, जारी the search. */
	पूर्ण
	/*
	 * We have finished with this index buffer without success.  Check क्रम
	 * the presence of a child node and अगर not present वापस -ENOENT.
	 */
	अगर (!(ie->flags & INDEX_ENTRY_NODE)) अणु
		ntfs_debug("Entry not found.");
		err = -ENOENT;
		जाओ ia_करोne;
	पूर्ण
	अगर ((ia->index.flags & NODE_MASK) == LEAF_NODE) अणु
		ntfs_error(sb, "Index entry with child node found in a leaf "
				"node in inode 0x%lx.", idx_ni->mft_no);
		जाओ unm_err_out;
	पूर्ण
	/* Child node present, descend पूर्णांकo it. */
	old_vcn = vcn;
	vcn = sle64_to_cpup((sle64*)((u8*)ie + le16_to_cpu(ie->length) - 8));
	अगर (vcn >= 0) अणु
		/*
		 * If vcn is in the same page cache page as old_vcn we recycle
		 * the mapped page.
		 */
		अगर (old_vcn << vol->cluster_size_bits >>
				PAGE_SHIFT == vcn <<
				vol->cluster_size_bits >>
				PAGE_SHIFT)
			जाओ fast_descend_पूर्णांकo_child_node;
		unlock_page(page);
		ntfs_unmap_page(page);
		जाओ descend_पूर्णांकo_child_node;
	पूर्ण
	ntfs_error(sb, "Negative child node vcn in inode 0x%lx.",
			idx_ni->mft_no);
unm_err_out:
	unlock_page(page);
	ntfs_unmap_page(page);
err_out:
	अगर (!err)
		err = -EIO;
	अगर (actx)
		ntfs_attr_put_search_ctx(actx);
	अगर (m)
		unmap_mft_record(base_ni);
	वापस err;
idx_err_out:
	ntfs_error(sb, "Corrupt index.  Aborting lookup.");
	जाओ err_out;
पूर्ण
