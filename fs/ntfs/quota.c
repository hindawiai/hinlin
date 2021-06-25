<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * quota.c - NTFS kernel quota ($Quota) handling.  Part of the Linux-NTFS
 *	     project.
 *
 * Copyright (c) 2004 Anton Altaparmakov
 */

#अगर_घोषित NTFS_RW

#समावेश "index.h"
#समावेश "quota.h"
#समावेश "debug.h"
#समावेश "ntfs.h"

/**
 * ntfs_mark_quotas_out_of_date - mark the quotas out of date on an ntfs volume
 * @vol:	ntfs volume on which to mark the quotas out of date
 *
 * Mark the quotas out of date on the ntfs volume @vol and वापस 'true' on
 * success and 'false' on error.
 */
bool ntfs_mark_quotas_out_of_date(ntfs_volume *vol)
अणु
	ntfs_index_context *ictx;
	QUOTA_CONTROL_ENTRY *qce;
	स्थिर le32 qid = QUOTA_DEFAULTS_ID;
	पूर्णांक err;

	ntfs_debug("Entering.");
	अगर (NVolQuotaOutOfDate(vol))
		जाओ करोne;
	अगर (!vol->quota_ino || !vol->quota_q_ino) अणु
		ntfs_error(vol->sb, "Quota inodes are not open.");
		वापस false;
	पूर्ण
	inode_lock(vol->quota_q_ino);
	ictx = ntfs_index_ctx_get(NTFS_I(vol->quota_q_ino));
	अगर (!ictx) अणु
		ntfs_error(vol->sb, "Failed to get index context.");
		जाओ err_out;
	पूर्ण
	err = ntfs_index_lookup(&qid, माप(qid), ictx);
	अगर (err) अणु
		अगर (err == -ENOENT)
			ntfs_error(vol->sb, "Quota defaults entry is not "
					"present.");
		अन्यथा
			ntfs_error(vol->sb, "Lookup of quota defaults entry "
					"failed.");
		जाओ err_out;
	पूर्ण
	अगर (ictx->data_len < दुरत्व(QUOTA_CONTROL_ENTRY, sid)) अणु
		ntfs_error(vol->sb, "Quota defaults entry size is invalid.  "
				"Run chkdsk.");
		जाओ err_out;
	पूर्ण
	qce = (QUOTA_CONTROL_ENTRY*)ictx->data;
	अगर (le32_to_cpu(qce->version) != QUOTA_VERSION) अणु
		ntfs_error(vol->sb, "Quota defaults entry version 0x%x is not "
				"supported.", le32_to_cpu(qce->version));
		जाओ err_out;
	पूर्ण
	ntfs_debug("Quota defaults flags = 0x%x.", le32_to_cpu(qce->flags));
	/* If quotas are alपढ़ोy marked out of date, no need to करो anything. */
	अगर (qce->flags & QUOTA_FLAG_OUT_OF_DATE)
		जाओ set_करोne;
	/*
	 * If quota tracking is neither requested, nor enabled and there are no
	 * pending deletes, no need to mark the quotas out of date.
	 */
	अगर (!(qce->flags & (QUOTA_FLAG_TRACKING_ENABLED |
			QUOTA_FLAG_TRACKING_REQUESTED |
			QUOTA_FLAG_PENDING_DELETES)))
		जाओ set_करोne;
	/*
	 * Set the QUOTA_FLAG_OUT_OF_DATE bit thus marking quotas out of date.
	 * This is verअगरied on WinXP to be sufficient to cause winकरोws to
	 * rescan the volume on boot and update all quota entries.
	 */
	qce->flags |= QUOTA_FLAG_OUT_OF_DATE;
	/* Ensure the modअगरied flags are written to disk. */
	ntfs_index_entry_flush_dcache_page(ictx);
	ntfs_index_entry_mark_dirty(ictx);
set_करोne:
	ntfs_index_ctx_put(ictx);
	inode_unlock(vol->quota_q_ino);
	/*
	 * We set the flag so we करो not try to mark the quotas out of date
	 * again on remount.
	 */
	NVolSetQuotaOutOfDate(vol);
करोne:
	ntfs_debug("Done.");
	वापस true;
err_out:
	अगर (ictx)
		ntfs_index_ctx_put(ictx);
	inode_unlock(vol->quota_q_ino);
	वापस false;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
