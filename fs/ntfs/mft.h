<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * mft.h - Defines क्रम mft record handling in NTFS Linux kernel driver.
 *	   Part of the Linux-NTFS project.
 *
 * Copyright (c) 2001-2004 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_MFT_H
#घोषणा _LINUX_NTFS_MFT_H

#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>

#समावेश "inode.h"

बाह्य MFT_RECORD *map_mft_record(ntfs_inode *ni);
बाह्य व्योम unmap_mft_record(ntfs_inode *ni);

बाह्य MFT_RECORD *map_extent_mft_record(ntfs_inode *base_ni, MFT_REF mref,
		ntfs_inode **ntfs_ino);

अटल अंतरभूत व्योम unmap_extent_mft_record(ntfs_inode *ni)
अणु
	unmap_mft_record(ni);
	वापस;
पूर्ण

#अगर_घोषित NTFS_RW

/**
 * flush_dcache_mft_record_page - flush_dcache_page() क्रम mft records
 * @ni:		ntfs inode काष्ठाure of mft record
 *
 * Call flush_dcache_page() क्रम the page in which an mft record resides.
 *
 * This must be called every समय an mft record is modअगरied, just after the
 * modअगरication.
 */
अटल अंतरभूत व्योम flush_dcache_mft_record_page(ntfs_inode *ni)
अणु
	flush_dcache_page(ni->page);
पूर्ण

बाह्य व्योम __mark_mft_record_dirty(ntfs_inode *ni);

/**
 * mark_mft_record_dirty - set the mft record and the page containing it dirty
 * @ni:		ntfs inode describing the mapped mft record
 *
 * Set the mapped (extent) mft record of the (base or extent) ntfs inode @ni,
 * as well as the page containing the mft record, dirty.  Also, mark the base
 * vfs inode dirty.  This ensures that any changes to the mft record are
 * written out to disk.
 *
 * NOTE:  Do not करो anything अगर the mft record is alपढ़ोy marked dirty.
 */
अटल अंतरभूत व्योम mark_mft_record_dirty(ntfs_inode *ni)
अणु
	अगर (!NInoTestSetDirty(ni))
		__mark_mft_record_dirty(ni);
पूर्ण

बाह्य पूर्णांक ntfs_sync_mft_mirror(ntfs_volume *vol, स्थिर अचिन्हित दीर्घ mft_no,
		MFT_RECORD *m, पूर्णांक sync);

बाह्य पूर्णांक ग_लिखो_mft_record_nolock(ntfs_inode *ni, MFT_RECORD *m, पूर्णांक sync);

/**
 * ग_लिखो_mft_record - ग_लिखो out a mapped (extent) mft record
 * @ni:		ntfs inode describing the mapped (extent) mft record
 * @m:		mapped (extent) mft record to ग_लिखो
 * @sync:	अगर true, रुको क्रम i/o completion
 *
 * This is just a wrapper क्रम ग_लिखो_mft_record_nolock() (see mft.c), which
 * locks the page क्रम the duration of the ग_लिखो.  This ensures that there are
 * no race conditions between writing the mft record via the dirty inode code
 * paths and via the page cache ग_लिखो back code paths or between writing
 * neighbouring mft records residing in the same page.
 *
 * Locking the page also serializes us against ->पढ़ोpage() अगर the page is not
 * uptodate.
 *
 * On success, clean the mft record and वापस 0.  On error, leave the mft
 * record dirty and वापस -त्रुटि_सं.
 */
अटल अंतरभूत पूर्णांक ग_लिखो_mft_record(ntfs_inode *ni, MFT_RECORD *m, पूर्णांक sync)
अणु
	काष्ठा page *page = ni->page;
	पूर्णांक err;

	BUG_ON(!page);
	lock_page(page);
	err = ग_लिखो_mft_record_nolock(ni, m, sync);
	unlock_page(page);
	वापस err;
पूर्ण

बाह्य bool ntfs_may_ग_लिखो_mft_record(ntfs_volume *vol,
		स्थिर अचिन्हित दीर्घ mft_no, स्थिर MFT_RECORD *m,
		ntfs_inode **locked_ni);

बाह्य ntfs_inode *ntfs_mft_record_alloc(ntfs_volume *vol, स्थिर पूर्णांक mode,
		ntfs_inode *base_ni, MFT_RECORD **mrec);
बाह्य पूर्णांक ntfs_extent_mft_record_मुक्त(ntfs_inode *ni, MFT_RECORD *m);

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_MFT_H */
