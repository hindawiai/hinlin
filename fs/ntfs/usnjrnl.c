<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * usnjrnl.h - NTFS kernel transaction log ($UsnJrnl) handling.  Part of the
 *	       Linux-NTFS project.
 *
 * Copyright (c) 2005 Anton Altaparmakov
 */

#अगर_घोषित NTFS_RW

#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/mm.h>

#समावेश "aops.h"
#समावेश "debug.h"
#समावेश "endian.h"
#समावेश "time.h"
#समावेश "types.h"
#समावेश "usnjrnl.h"
#समावेश "volume.h"

/**
 * ntfs_stamp_usnjrnl - stamp the transaction log ($UsnJrnl) on an ntfs volume
 * @vol:	ntfs volume on which to stamp the transaction log
 *
 * Stamp the transaction log ($UsnJrnl) on the ntfs volume @vol and वापस
 * 'true' on success and 'false' on error.
 *
 * This function assumes that the transaction log has alपढ़ोy been loaded and
 * consistency checked by a call to fs/ntfs/super.c::load_and_init_usnjrnl().
 */
bool ntfs_stamp_usnjrnl(ntfs_volume *vol)
अणु
	ntfs_debug("Entering.");
	अगर (likely(!NVolUsnJrnlStamped(vol))) अणु
		sle64 stamp;
		काष्ठा page *page;
		USN_HEADER *uh;

		page = ntfs_map_page(vol->usnjrnl_max_ino->i_mapping, 0);
		अगर (IS_ERR(page)) अणु
			ntfs_error(vol->sb, "Failed to read from "
					"$UsnJrnl/$DATA/$Max attribute.");
			वापस false;
		पूर्ण
		uh = (USN_HEADER*)page_address(page);
		stamp = get_current_ntfs_समय();
		ntfs_debug("Stamping transaction log ($UsnJrnl): old "
				"journal_id 0x%llx, old lowest_valid_usn "
				"0x%llx, new journal_id 0x%llx, new "
				"lowest_valid_usn 0x%llx.",
				(दीर्घ दीर्घ)sle64_to_cpu(uh->journal_id),
				(दीर्घ दीर्घ)sle64_to_cpu(uh->lowest_valid_usn),
				(दीर्घ दीर्घ)sle64_to_cpu(stamp),
				i_size_पढ़ो(vol->usnjrnl_j_ino));
		uh->lowest_valid_usn =
				cpu_to_sle64(i_size_पढ़ो(vol->usnjrnl_j_ino));
		uh->journal_id = stamp;
		flush_dcache_page(page);
		set_page_dirty(page);
		ntfs_unmap_page(page);
		/* Set the flag so we करो not have to करो it again on remount. */
		NVolSetUsnJrnlStamped(vol);
	पूर्ण
	ntfs_debug("Done.");
	वापस true;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
