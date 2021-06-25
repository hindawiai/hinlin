<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * index.h - Defines क्रम NTFS kernel index handling.  Part of the Linux-NTFS
 *	     project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_INDEX_H
#घोषणा _LINUX_NTFS_INDEX_H

#समावेश <linux/fs.h>

#समावेश "types.h"
#समावेश "layout.h"
#समावेश "inode.h"
#समावेश "attrib.h"
#समावेश "mft.h"
#समावेश "aops.h"

/**
 * @idx_ni:	index inode containing the @entry described by this context
 * @entry:	index entry (poपूर्णांकs पूर्णांकo @ir or @ia)
 * @data:	index entry data (poपूर्णांकs पूर्णांकo @entry)
 * @data_len:	length in bytes of @data
 * @is_in_root:	'true' if @entry is in @ir and 'false' अगर it is in @ia
 * @ir:		index root अगर @is_in_root and शून्य otherwise
 * @actx:	attribute search context अगर @is_in_root and शून्य otherwise
 * @base_ni:	base inode अगर @is_in_root and शून्य otherwise
 * @ia:		index block अगर @is_in_root is 'false' and शून्य otherwise
 * @page:	page अगर @is_in_root is 'false' and शून्य otherwise
 *
 * @idx_ni is the index inode this context beदीर्घs to.
 *
 * @entry is the index entry described by this context.  @data and @data_len
 * are the index entry data and its length in bytes, respectively.  @data
 * simply poपूर्णांकs पूर्णांकo @entry.  This is probably what the user is पूर्णांकerested in.
 *
 * If @is_in_root is 'true', @entry is in the index root attribute @ir described
 * by the attribute search context @actx and the base inode @base_ni.  @ia and
 * @page are शून्य in this हाल.
 *
 * If @is_in_root is 'false', @entry is in the index allocation attribute and @ia
 * and @page poपूर्णांक to the index allocation block and the mapped, locked page it
 * is in, respectively.  @ir, @actx and @base_ni are शून्य in this हाल.
 *
 * To obtain a context call ntfs_index_ctx_get().
 *
 * We use this context to allow ntfs_index_lookup() to वापस the found index
 * @entry and its @data without having to allocate a buffer and copy the @entry
 * and/or its @data पूर्णांकo it.
 *
 * When finished with the @entry and its @data, call ntfs_index_ctx_put() to
 * मुक्त the context and other associated resources.
 *
 * If the index entry was modअगरied, call flush_dcache_index_entry_page()
 * immediately after the modअगरication and either ntfs_index_entry_mark_dirty()
 * or ntfs_index_entry_ग_लिखो() beक्रमe the call to ntfs_index_ctx_put() to
 * ensure that the changes are written to disk.
 */
प्रकार काष्ठा अणु
	ntfs_inode *idx_ni;
	INDEX_ENTRY *entry;
	व्योम *data;
	u16 data_len;
	bool is_in_root;
	INDEX_ROOT *ir;
	ntfs_attr_search_ctx *actx;
	ntfs_inode *base_ni;
	INDEX_ALLOCATION *ia;
	काष्ठा page *page;
पूर्ण ntfs_index_context;

बाह्य ntfs_index_context *ntfs_index_ctx_get(ntfs_inode *idx_ni);
बाह्य व्योम ntfs_index_ctx_put(ntfs_index_context *ictx);

बाह्य पूर्णांक ntfs_index_lookup(स्थिर व्योम *key, स्थिर पूर्णांक key_len,
		ntfs_index_context *ictx);

#अगर_घोषित NTFS_RW

/**
 * ntfs_index_entry_flush_dcache_page - flush_dcache_page() क्रम index entries
 * @ictx:	ntfs index context describing the index entry
 *
 * Call flush_dcache_page() क्रम the page in which an index entry resides.
 *
 * This must be called every समय an index entry is modअगरied, just after the
 * modअगरication.
 *
 * If the index entry is in the index root attribute, simply flush the page
 * containing the mft record containing the index root attribute.
 *
 * If the index entry is in an index block beदीर्घing to the index allocation
 * attribute, simply flush the page cache page containing the index block.
 */
अटल अंतरभूत व्योम ntfs_index_entry_flush_dcache_page(ntfs_index_context *ictx)
अणु
	अगर (ictx->is_in_root)
		flush_dcache_mft_record_page(ictx->actx->ntfs_ino);
	अन्यथा
		flush_dcache_page(ictx->page);
पूर्ण

/**
 * ntfs_index_entry_mark_dirty - mark an index entry dirty
 * @ictx:	ntfs index context describing the index entry
 *
 * Mark the index entry described by the index entry context @ictx dirty.
 *
 * If the index entry is in the index root attribute, simply mark the mft
 * record containing the index root attribute dirty.  This ensures the mft
 * record, and hence the index root attribute, will be written out to disk
 * later.
 *
 * If the index entry is in an index block beदीर्घing to the index allocation
 * attribute, mark the buffers beदीर्घing to the index record as well as the
 * page cache page the index block is in dirty.  This स्वतःmatically marks the
 * VFS inode of the ntfs index inode to which the index entry beदीर्घs dirty,
 * too (I_सूचीTY_PAGES) and this in turn ensures the page buffers, and hence the
 * dirty index block, will be written out to disk later.
 */
अटल अंतरभूत व्योम ntfs_index_entry_mark_dirty(ntfs_index_context *ictx)
अणु
	अगर (ictx->is_in_root)
		mark_mft_record_dirty(ictx->actx->ntfs_ino);
	अन्यथा
		mark_ntfs_record_dirty(ictx->page,
				(u8*)ictx->ia - (u8*)page_address(ictx->page));
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_INDEX_H */
