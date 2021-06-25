<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2019 HUAWEI, Inc.
 *             https://www.huawei.com/
 * Created by Gao Xiang <gaoxiang25@huawei.com>
 */
#अगर_अघोषित __EROFS_FS_COMPRESS_H
#घोषणा __EROFS_FS_COMPRESS_H

#समावेश "internal.h"

क्रमागत अणु
	Z_EROFS_COMPRESSION_SHIFTED = Z_EROFS_COMPRESSION_MAX,
	Z_EROFS_COMPRESSION_RUNTIME_MAX
पूर्ण;

काष्ठा z_erofs_decompress_req अणु
	काष्ठा super_block *sb;
	काष्ठा page **in, **out;

	अचिन्हित लघु pageofs_out;
	अचिन्हित पूर्णांक inमाला_दोize, outमाला_दोize;

	/* indicate the algorithm will be used क्रम decompression */
	अचिन्हित पूर्णांक alg;
	bool inplace_io, partial_decoding;
पूर्ण;

/* some special page->निजी (अचिन्हित दीर्घ, see below) */
#घोषणा Z_EROFS_SHORTLIVED_PAGE		(-1UL << 2)
#घोषणा Z_EROFS_PREALLOCATED_PAGE	(-2UL << 2)

/*
 * For all pages in a pcluster, page->निजी should be one of
 * Type                         Last 2bits      page->निजी
 * लघु-lived page             00              Z_EROFS_SHORTLIVED_PAGE
 * pपुनः_स्मृतिated page (tryalloc) 00              Z_EROFS_PREALLOCATED_PAGE
 * cached/managed page          00              poपूर्णांकer to z_erofs_pcluster
 * online page (file-backed,    01/10/11        sub-index << 2 | count
 *              some pages can be used क्रम inplace I/O)
 *
 * page->mapping should be one of
 * Type                 page->mapping
 * लघु-lived page     शून्य
 * pपुनः_स्मृतिated page    शून्य
 * cached/managed page  non-शून्य or शून्य (invalidated/truncated page)
 * online page          non-शून्य
 *
 * For all managed pages, PG_निजी should be set with 1 extra refcount,
 * which is used क्रम page reclaim / migration.
 */

/*
 * लघु-lived pages are pages directly from buddy प्रणाली with specअगरic
 * page->निजी (no need to set PagePrivate since these are non-LRU /
 * non-movable pages and bypass reclaim / migration code).
 */
अटल अंतरभूत bool z_erofs_is_लघुlived_page(काष्ठा page *page)
अणु
	अगर (page->निजी != Z_EROFS_SHORTLIVED_PAGE)
		वापस false;

	DBG_BUGON(page->mapping);
	वापस true;
पूर्ण

अटल अंतरभूत bool z_erofs_put_लघुlivedpage(काष्ठा list_head *pagepool,
					      काष्ठा page *page)
अणु
	अगर (!z_erofs_is_लघुlived_page(page))
		वापस false;

	/* लघु-lived pages should not be used by others at the same समय */
	अगर (page_ref_count(page) > 1) अणु
		put_page(page);
	पूर्ण अन्यथा अणु
		/* follow the pcluster rule above. */
		set_page_निजी(page, 0);
		list_add(&page->lru, pagepool);
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक z_erofs_decompress(काष्ठा z_erofs_decompress_req *rq,
		       काष्ठा list_head *pagepool);

#पूर्ण_अगर

