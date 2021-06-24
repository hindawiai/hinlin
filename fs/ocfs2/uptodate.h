<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * uptodate.h
 *
 * Cluster uptodate tracking
 *
 * Copyright (C) 2002, 2004, 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_UPTODATE_H
#घोषणा OCFS2_UPTODATE_H

/*
 * The caching code relies on locking provided by the user of
 * काष्ठा ocfs2_caching_info.  These operations connect that up.
 */
काष्ठा ocfs2_caching_operations अणु
	/*
	 * A u64 representing the owning काष्ठाure.  Usually this
	 * is the block number (i_blkno or whatnot).  This is used so
	 * that caching log messages can identअगरy the owning काष्ठाure.
	 */
	u64	(*co_owner)(काष्ठा ocfs2_caching_info *ci);

	/* The superblock is needed during I/O. */
	काष्ठा super_block *(*co_get_super)(काष्ठा ocfs2_caching_info *ci);
	/*
	 * Lock and unlock the caching data.  These will not sleep, and
	 * should probably be spinlocks.
	 */
	व्योम	(*co_cache_lock)(काष्ठा ocfs2_caching_info *ci);
	व्योम	(*co_cache_unlock)(काष्ठा ocfs2_caching_info *ci);

	/*
	 * Lock and unlock क्रम disk I/O.  These will sleep, and should
	 * be mutexes.
	 */
	व्योम	(*co_io_lock)(काष्ठा ocfs2_caching_info *ci);
	व्योम	(*co_io_unlock)(काष्ठा ocfs2_caching_info *ci);
पूर्ण;

पूर्णांक __init init_ocfs2_uptodate_cache(व्योम);
व्योम निकास_ocfs2_uptodate_cache(व्योम);

व्योम ocfs2_metadata_cache_init(काष्ठा ocfs2_caching_info *ci,
			       स्थिर काष्ठा ocfs2_caching_operations *ops);
व्योम ocfs2_metadata_cache_purge(काष्ठा ocfs2_caching_info *ci);
व्योम ocfs2_metadata_cache_निकास(काष्ठा ocfs2_caching_info *ci);

u64 ocfs2_metadata_cache_owner(काष्ठा ocfs2_caching_info *ci);
व्योम ocfs2_metadata_cache_io_lock(काष्ठा ocfs2_caching_info *ci);
व्योम ocfs2_metadata_cache_io_unlock(काष्ठा ocfs2_caching_info *ci);

पूर्णांक ocfs2_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
			  काष्ठा buffer_head *bh);
व्योम ocfs2_set_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
			       काष्ठा buffer_head *bh);
व्योम ocfs2_set_new_buffer_uptodate(काष्ठा ocfs2_caching_info *ci,
				   काष्ठा buffer_head *bh);
व्योम ocfs2_हटाओ_from_cache(काष्ठा ocfs2_caching_info *ci,
			     काष्ठा buffer_head *bh);
व्योम ocfs2_हटाओ_xattr_clusters_from_cache(काष्ठा ocfs2_caching_info *ci,
					    sector_t block,
					    u32 c_len);
पूर्णांक ocfs2_buffer_पढ़ो_ahead(काष्ठा ocfs2_caching_info *ci,
			    काष्ठा buffer_head *bh);

#पूर्ण_अगर /* OCFS2_UPTODATE_H */
