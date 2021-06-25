<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/**
 * aops.h - Defines क्रम NTFS kernel address space operations and page cache
 *	    handling.  Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_AOPS_H
#घोषणा _LINUX_NTFS_AOPS_H

#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>
#समावेश <linux/fs.h>

#समावेश "inode.h"

/**
 * ntfs_unmap_page - release a page that was mapped using ntfs_map_page()
 * @page:	the page to release
 *
 * Unpin, unmap and release a page that was obtained from ntfs_map_page().
 */
अटल अंतरभूत व्योम ntfs_unmap_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

/**
 * ntfs_map_page - map a page पूर्णांकo accessible memory, पढ़ोing it अगर necessary
 * @mapping:	address space क्रम which to obtain the page
 * @index:	index पूर्णांकo the page cache क्रम @mapping of the page to map
 *
 * Read a page from the page cache of the address space @mapping at position
 * @index, where @index is in units of PAGE_SIZE, and not in bytes.
 *
 * If the page is not in memory it is loaded from disk first using the पढ़ोpage
 * method defined in the address space operations of @mapping and the page is
 * added to the page cache of @mapping in the process.
 *
 * If the page beदीर्घs to an mst रक्षित attribute and it is marked as such
 * in its ntfs inode (NInoMstProtected()) the mst fixups are applied but no
 * error checking is perक्रमmed.  This means the caller has to verअगरy whether
 * the ntfs record(s) contained in the page are valid or not using one of the
 * ntfs_is_XXXX_recordअणु,pपूर्ण() macros, where XXXX is the record type you are
 * expecting to see.  (For details of the macros, see fs/ntfs/layout.h.)
 *
 * If the page is in high memory it is mapped पूर्णांकo memory directly addressible
 * by the kernel.
 *
 * Finally the page count is incremented, thus pinning the page पूर्णांकo place.
 *
 * The above means that page_address(page) can be used on all pages obtained
 * with ntfs_map_page() to get the kernel भव address of the page.
 *
 * When finished with the page, the caller has to call ntfs_unmap_page() to
 * unpin, unmap and release the page.
 *
 * Note this करोes not grant exclusive access. If such is desired, the caller
 * must provide it independently of the ntfs_अणुunपूर्णmap_page() calls by using
 * a अणुrw_पूर्णsemaphore or other means of serialization. A spin lock cannot be
 * used as ntfs_map_page() can block.
 *
 * The unlocked and uptodate page is वापसed on success or an encoded error
 * on failure. Caller has to test क्रम error using the IS_ERR() macro on the
 * वापस value. If that evaluates to 'true', the negative error code can be
 * obtained using PTR_ERR() on the वापस value of ntfs_map_page().
 */
अटल अंतरभूत काष्ठा page *ntfs_map_page(काष्ठा address_space *mapping,
		अचिन्हित दीर्घ index)
अणु
	काष्ठा page *page = पढ़ो_mapping_page(mapping, index, शून्य);

	अगर (!IS_ERR(page)) अणु
		kmap(page);
		अगर (!PageError(page))
			वापस page;
		ntfs_unmap_page(page);
		वापस ERR_PTR(-EIO);
	पूर्ण
	वापस page;
पूर्ण

#अगर_घोषित NTFS_RW

बाह्य व्योम mark_ntfs_record_dirty(काष्ठा page *page, स्थिर अचिन्हित पूर्णांक ofs);

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_AOPS_H */
