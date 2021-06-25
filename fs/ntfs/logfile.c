<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * logfile.c - NTFS kernel journal handling. Part of the Linux-NTFS project.
 *
 * Copyright (c) 2002-2007 Anton Altaparmakov
 */

#अगर_घोषित NTFS_RW

#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/buffer_head.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/bपन.स>

#समावेश "attrib.h"
#समावेश "aops.h"
#समावेश "debug.h"
#समावेश "logfile.h"
#समावेश "malloc.h"
#समावेश "volume.h"
#समावेश "ntfs.h"

/**
 * ntfs_check_restart_page_header - check the page header क्रम consistency
 * @vi:		$LogFile inode to which the restart page header beदीर्घs
 * @rp:		restart page header to check
 * @pos:	position in @vi at which the restart page header resides
 *
 * Check the restart page header @rp क्रम consistency and वापस 'true' अगर it is
 * consistent and 'false' otherwise.
 *
 * This function only needs NTFS_BLOCK_SIZE bytes in @rp, i.e. it करोes not
 * require the full restart page.
 */
अटल bool ntfs_check_restart_page_header(काष्ठा inode *vi,
		RESTART_PAGE_HEADER *rp, s64 pos)
अणु
	u32 logfile_प्रणाली_page_size, logfile_log_page_size;
	u16 ra_ofs, usa_count, usa_ofs, usa_end = 0;
	bool have_usa = true;

	ntfs_debug("Entering.");
	/*
	 * If the प्रणाली or log page sizes are smaller than the ntfs block size
	 * or either is not a घातer of 2 we cannot handle this log file.
	 */
	logfile_प्रणाली_page_size = le32_to_cpu(rp->प्रणाली_page_size);
	logfile_log_page_size = le32_to_cpu(rp->log_page_size);
	अगर (logfile_प्रणाली_page_size < NTFS_BLOCK_SIZE ||
			logfile_log_page_size < NTFS_BLOCK_SIZE ||
			logfile_प्रणाली_page_size &
			(logfile_प्रणाली_page_size - 1) ||
			!is_घातer_of_2(logfile_log_page_size)) अणु
		ntfs_error(vi->i_sb, "$LogFile uses unsupported page size.");
		वापस false;
	पूर्ण
	/*
	 * We must be either at !pos (1st restart page) or at pos = प्रणाली page
	 * size (2nd restart page).
	 */
	अगर (pos && pos != logfile_प्रणाली_page_size) अणु
		ntfs_error(vi->i_sb, "Found restart area in incorrect "
				"position in $LogFile.");
		वापस false;
	पूर्ण
	/* We only know how to handle version 1.1. */
	अगर (sle16_to_cpu(rp->major_ver) != 1 ||
			sle16_to_cpu(rp->minor_ver) != 1) अणु
		ntfs_error(vi->i_sb, "$LogFile version %i.%i is not "
				"supported.  (This driver supports version "
				"1.1 only.)", (पूर्णांक)sle16_to_cpu(rp->major_ver),
				(पूर्णांक)sle16_to_cpu(rp->minor_ver));
		वापस false;
	पूर्ण
	/*
	 * If chkdsk has been run the restart page may not be रक्षित by an
	 * update sequence array.
	 */
	अगर (ntfs_is_chkd_record(rp->magic) && !le16_to_cpu(rp->usa_count)) अणु
		have_usa = false;
		जाओ skip_usa_checks;
	पूर्ण
	/* Verअगरy the size of the update sequence array. */
	usa_count = 1 + (logfile_प्रणाली_page_size >> NTFS_BLOCK_SIZE_BITS);
	अगर (usa_count != le16_to_cpu(rp->usa_count)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart page specifies "
				"inconsistent update sequence array count.");
		वापस false;
	पूर्ण
	/* Verअगरy the position of the update sequence array. */
	usa_ofs = le16_to_cpu(rp->usa_ofs);
	usa_end = usa_ofs + usa_count * माप(u16);
	अगर (usa_ofs < माप(RESTART_PAGE_HEADER) ||
			usa_end > NTFS_BLOCK_SIZE - माप(u16)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart page specifies "
				"inconsistent update sequence array offset.");
		वापस false;
	पूर्ण
skip_usa_checks:
	/*
	 * Verअगरy the position of the restart area.  It must be:
	 *	- aligned to 8-byte boundary,
	 *	- after the update sequence array, and
	 *	- within the प्रणाली page size.
	 */
	ra_ofs = le16_to_cpu(rp->restart_area_offset);
	अगर (ra_ofs & 7 || (have_usa ? ra_ofs < usa_end :
			ra_ofs < माप(RESTART_PAGE_HEADER)) ||
			ra_ofs > logfile_प्रणाली_page_size) अणु
		ntfs_error(vi->i_sb, "$LogFile restart page specifies "
				"inconsistent restart area offset.");
		वापस false;
	पूर्ण
	/*
	 * Only restart pages modअगरied by chkdsk are allowed to have chkdsk_lsn
	 * set.
	 */
	अगर (!ntfs_is_chkd_record(rp->magic) && sle64_to_cpu(rp->chkdsk_lsn)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart page is not modified "
				"by chkdsk but a chkdsk LSN is specified.");
		वापस false;
	पूर्ण
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * ntfs_check_restart_area - check the restart area क्रम consistency
 * @vi:		$LogFile inode to which the restart page beदीर्घs
 * @rp:		restart page whose restart area to check
 *
 * Check the restart area of the restart page @rp क्रम consistency and वापस
 * 'true' if it is consistent and 'false' otherwise.
 *
 * This function assumes that the restart page header has alपढ़ोy been
 * consistency checked.
 *
 * This function only needs NTFS_BLOCK_SIZE bytes in @rp, i.e. it करोes not
 * require the full restart page.
 */
अटल bool ntfs_check_restart_area(काष्ठा inode *vi, RESTART_PAGE_HEADER *rp)
अणु
	u64 file_size;
	RESTART_AREA *ra;
	u16 ra_ofs, ra_len, ca_ofs;
	u8 fs_bits;

	ntfs_debug("Entering.");
	ra_ofs = le16_to_cpu(rp->restart_area_offset);
	ra = (RESTART_AREA*)((u8*)rp + ra_ofs);
	/*
	 * Everything beक्रमe ra->file_size must be beक्रमe the first word
	 * रक्षित by an update sequence number.  This ensures that it is
	 * safe to access ra->client_array_offset.
	 */
	अगर (ra_ofs + दुरत्व(RESTART_AREA, file_size) >
			NTFS_BLOCK_SIZE - माप(u16)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent file offset.");
		वापस false;
	पूर्ण
	/*
	 * Now that we can access ra->client_array_offset, make sure everything
	 * up to the log client array is beक्रमe the first word रक्षित by an
	 * update sequence number.  This ensures we can access all of the
	 * restart area elements safely.  Also, the client array offset must be
	 * aligned to an 8-byte boundary.
	 */
	ca_ofs = le16_to_cpu(ra->client_array_offset);
	अगर (((ca_ofs + 7) & ~7) != ca_ofs ||
			ra_ofs + ca_ofs > NTFS_BLOCK_SIZE - माप(u16)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent client array offset.");
		वापस false;
	पूर्ण
	/*
	 * The restart area must end within the प्रणाली page size both when
	 * calculated manually and as specअगरied by ra->restart_area_length.
	 * Also, the calculated length must not exceed the specअगरied length.
	 */
	ra_len = ca_ofs + le16_to_cpu(ra->log_clients) *
			माप(LOG_CLIENT_RECORD);
	अगर (ra_ofs + ra_len > le32_to_cpu(rp->प्रणाली_page_size) ||
			ra_ofs + le16_to_cpu(ra->restart_area_length) >
			le32_to_cpu(rp->प्रणाली_page_size) ||
			ra_len > le16_to_cpu(ra->restart_area_length)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area is out of bounds "
				"of the system page size specified by the "
				"restart page header and/or the specified "
				"restart area length is inconsistent.");
		वापस false;
	पूर्ण
	/*
	 * The ra->client_मुक्त_list and ra->client_in_use_list must be either
	 * LOGखाता_NO_CLIENT or less than ra->log_clients or they are
	 * overflowing the client array.
	 */
	अगर ((ra->client_मुक्त_list != LOGखाता_NO_CLIENT &&
			le16_to_cpu(ra->client_मुक्त_list) >=
			le16_to_cpu(ra->log_clients)) ||
			(ra->client_in_use_list != LOGखाता_NO_CLIENT &&
			le16_to_cpu(ra->client_in_use_list) >=
			le16_to_cpu(ra->log_clients))) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"overflowing client free and/or in use lists.");
		वापस false;
	पूर्ण
	/*
	 * Check ra->seq_number_bits against ra->file_size क्रम consistency.
	 * We cannot just use ffs() because the file size is not a घातer of 2.
	 */
	file_size = (u64)sle64_to_cpu(ra->file_size);
	fs_bits = 0;
	जबतक (file_size) अणु
		file_size >>= 1;
		fs_bits++;
	पूर्ण
	अगर (le32_to_cpu(ra->seq_number_bits) != 67 - fs_bits) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent sequence number bits.");
		वापस false;
	पूर्ण
	/* The log record header length must be a multiple of 8. */
	अगर (((le16_to_cpu(ra->log_record_header_length) + 7) & ~7) !=
			le16_to_cpu(ra->log_record_header_length)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent log record header length.");
		वापस false;
	पूर्ण
	/* Dito क्रम the log page data offset. */
	अगर (((le16_to_cpu(ra->log_page_data_offset) + 7) & ~7) !=
			le16_to_cpu(ra->log_page_data_offset)) अणु
		ntfs_error(vi->i_sb, "$LogFile restart area specifies "
				"inconsistent log page data offset.");
		वापस false;
	पूर्ण
	ntfs_debug("Done.");
	वापस true;
पूर्ण

/**
 * ntfs_check_log_client_array - check the log client array क्रम consistency
 * @vi:		$LogFile inode to which the restart page beदीर्घs
 * @rp:		restart page whose log client array to check
 *
 * Check the log client array of the restart page @rp क्रम consistency and
 * वापस 'true' if it is consistent and 'false' otherwise.
 *
 * This function assumes that the restart page header and the restart area have
 * alपढ़ोy been consistency checked.
 *
 * Unlike ntfs_check_restart_page_header() and ntfs_check_restart_area(), this
 * function needs @rp->प्रणाली_page_size bytes in @rp, i.e. it requires the full
 * restart page and the page must be multi sector transfer deरक्षित.
 */
अटल bool ntfs_check_log_client_array(काष्ठा inode *vi,
		RESTART_PAGE_HEADER *rp)
अणु
	RESTART_AREA *ra;
	LOG_CLIENT_RECORD *ca, *cr;
	u16 nr_clients, idx;
	bool in_मुक्त_list, idx_is_first;

	ntfs_debug("Entering.");
	ra = (RESTART_AREA*)((u8*)rp + le16_to_cpu(rp->restart_area_offset));
	ca = (LOG_CLIENT_RECORD*)((u8*)ra +
			le16_to_cpu(ra->client_array_offset));
	/*
	 * Check the ra->client_मुक्त_list first and then check the
	 * ra->client_in_use_list.  Check each of the log client records in
	 * each of the lists and check that the array करोes not overflow the
	 * ra->log_clients value.  Also keep track of the number of records
	 * visited as there cannot be more than ra->log_clients records and
	 * that way we detect eventual loops in within a list.
	 */
	nr_clients = le16_to_cpu(ra->log_clients);
	idx = le16_to_cpu(ra->client_मुक्त_list);
	in_मुक्त_list = true;
check_list:
	क्रम (idx_is_first = true; idx != LOGखाता_NO_CLIENT_CPU; nr_clients--,
			idx = le16_to_cpu(cr->next_client)) अणु
		अगर (!nr_clients || idx >= le16_to_cpu(ra->log_clients))
			जाओ err_out;
		/* Set @cr to the current log client record. */
		cr = ca + idx;
		/* The first log client record must not have a prev_client. */
		अगर (idx_is_first) अणु
			अगर (cr->prev_client != LOGखाता_NO_CLIENT)
				जाओ err_out;
			idx_is_first = false;
		पूर्ण
	पूर्ण
	/* Switch to and check the in use list अगर we just did the मुक्त list. */
	अगर (in_मुक्त_list) अणु
		in_मुक्त_list = false;
		idx = le16_to_cpu(ra->client_in_use_list);
		जाओ check_list;
	पूर्ण
	ntfs_debug("Done.");
	वापस true;
err_out:
	ntfs_error(vi->i_sb, "$LogFile log client array is corrupt.");
	वापस false;
पूर्ण

/**
 * ntfs_check_and_load_restart_page - check the restart page क्रम consistency
 * @vi:		$LogFile inode to which the restart page beदीर्घs
 * @rp:		restart page to check
 * @pos:	position in @vi at which the restart page resides
 * @wrp:	[OUT] copy of the multi sector transfer deरक्षित restart page
 * @lsn:	[OUT] set to the current logfile lsn on success
 *
 * Check the restart page @rp क्रम consistency and वापस 0 अगर it is consistent
 * and -त्रुटि_सं otherwise.  The restart page may have been modअगरied by chkdsk in
 * which हाल its magic is CHKD instead of RSTR.
 *
 * This function only needs NTFS_BLOCK_SIZE bytes in @rp, i.e. it करोes not
 * require the full restart page.
 *
 * If @wrp is not शून्य, on success, *@wrp will poपूर्णांक to a buffer containing a
 * copy of the complete multi sector transfer deरक्षित page.  On failure,
 * *@wrp is undefined.
 *
 * Simillarly, अगर @lsn is not शून्य, on success *@lsn will be set to the current
 * logfile lsn according to this restart page.  On failure, *@lsn is undefined.
 *
 * The following error codes are defined:
 *	-EINVAL	- The restart page is inconsistent.
 *	-ENOMEM	- Not enough memory to load the restart page.
 *	-EIO	- Failed to पढ़ोing from $LogFile.
 */
अटल पूर्णांक ntfs_check_and_load_restart_page(काष्ठा inode *vi,
		RESTART_PAGE_HEADER *rp, s64 pos, RESTART_PAGE_HEADER **wrp,
		LSN *lsn)
अणु
	RESTART_AREA *ra;
	RESTART_PAGE_HEADER *trp;
	पूर्णांक size, err;

	ntfs_debug("Entering.");
	/* Check the restart page header क्रम consistency. */
	अगर (!ntfs_check_restart_page_header(vi, rp, pos)) अणु
		/* Error output alपढ़ोy करोne inside the function. */
		वापस -EINVAL;
	पूर्ण
	/* Check the restart area क्रम consistency. */
	अगर (!ntfs_check_restart_area(vi, rp)) अणु
		/* Error output alपढ़ोy करोne inside the function. */
		वापस -EINVAL;
	पूर्ण
	ra = (RESTART_AREA*)((u8*)rp + le16_to_cpu(rp->restart_area_offset));
	/*
	 * Allocate a buffer to store the whole restart page so we can multi
	 * sector transfer deprotect it.
	 */
	trp = ntfs_दो_स्मृति_nofs(le32_to_cpu(rp->प्रणाली_page_size));
	अगर (!trp) अणु
		ntfs_error(vi->i_sb, "Failed to allocate memory for $LogFile "
				"restart page buffer.");
		वापस -ENOMEM;
	पूर्ण
	/*
	 * Read the whole of the restart page पूर्णांकo the buffer.  If it fits
	 * completely inside @rp, just copy it from there.  Otherwise map all
	 * the required pages and copy the data from them.
	 */
	size = PAGE_SIZE - (pos & ~PAGE_MASK);
	अगर (size >= le32_to_cpu(rp->प्रणाली_page_size)) अणु
		स_नकल(trp, rp, le32_to_cpu(rp->प्रणाली_page_size));
	पूर्ण अन्यथा अणु
		pgoff_t idx;
		काष्ठा page *page;
		पूर्णांक have_पढ़ो, to_पढ़ो;

		/* First copy what we alपढ़ोy have in @rp. */
		स_नकल(trp, rp, size);
		/* Copy the reमुख्यing data one page at a समय. */
		have_पढ़ो = size;
		to_पढ़ो = le32_to_cpu(rp->प्रणाली_page_size) - size;
		idx = (pos + size) >> PAGE_SHIFT;
		BUG_ON((pos + size) & ~PAGE_MASK);
		करो अणु
			page = ntfs_map_page(vi->i_mapping, idx);
			अगर (IS_ERR(page)) अणु
				ntfs_error(vi->i_sb, "Error mapping $LogFile "
						"page (index %lu).", idx);
				err = PTR_ERR(page);
				अगर (err != -EIO && err != -ENOMEM)
					err = -EIO;
				जाओ err_out;
			पूर्ण
			size = min_t(पूर्णांक, to_पढ़ो, PAGE_SIZE);
			स_नकल((u8*)trp + have_पढ़ो, page_address(page), size);
			ntfs_unmap_page(page);
			have_पढ़ो += size;
			to_पढ़ो -= size;
			idx++;
		पूर्ण जबतक (to_पढ़ो > 0);
	पूर्ण
	/*
	 * Perक्रमm the multi sector transfer deprotection on the buffer अगर the
	 * restart page is रक्षित.
	 */
	अगर ((!ntfs_is_chkd_record(trp->magic) || le16_to_cpu(trp->usa_count))
			&& post_पढ़ो_mst_fixup((NTFS_RECORD*)trp,
			le32_to_cpu(rp->प्रणाली_page_size))) अणु
		/*
		 * A multi sector tranfer error was detected.  We only need to
		 * पात अगर the restart page contents exceed the multi sector
		 * transfer fixup of the first sector.
		 */
		अगर (le16_to_cpu(rp->restart_area_offset) +
				le16_to_cpu(ra->restart_area_length) >
				NTFS_BLOCK_SIZE - माप(u16)) अणु
			ntfs_error(vi->i_sb, "Multi sector transfer error "
					"detected in $LogFile restart page.");
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण
	/*
	 * If the restart page is modअगरied by chkdsk or there are no active
	 * logfile clients, the logfile is consistent.  Otherwise, need to
	 * check the log client records क्रम consistency, too.
	 */
	err = 0;
	अगर (ntfs_is_rstr_record(rp->magic) &&
			ra->client_in_use_list != LOGखाता_NO_CLIENT) अणु
		अगर (!ntfs_check_log_client_array(vi, trp)) अणु
			err = -EINVAL;
			जाओ err_out;
		पूर्ण
	पूर्ण
	अगर (lsn) अणु
		अगर (ntfs_is_rstr_record(rp->magic))
			*lsn = sle64_to_cpu(ra->current_lsn);
		अन्यथा /* अगर (ntfs_is_chkd_record(rp->magic)) */
			*lsn = sle64_to_cpu(rp->chkdsk_lsn);
	पूर्ण
	ntfs_debug("Done.");
	अगर (wrp)
		*wrp = trp;
	अन्यथा अणु
err_out:
		ntfs_मुक्त(trp);
	पूर्ण
	वापस err;
पूर्ण

/**
 * ntfs_check_logfile - check the journal क्रम consistency
 * @log_vi:	काष्ठा inode of loaded journal $LogFile to check
 * @rp:		[OUT] on success this is a copy of the current restart page
 *
 * Check the $LogFile journal क्रम consistency and वापस 'true' अगर it is
 * consistent and 'false' अगर not.  On success, the current restart page is
 * वापसed in *@rp.  Caller must call ntfs_मुक्त(*@rp) when finished with it.
 *
 * At present we only check the two restart pages and ignore the log record
 * pages.
 *
 * Note that the MstProtected flag is not set on the $LogFile inode and hence
 * when पढ़ोing pages they are not deरक्षित.  This is because we करो not know
 * अगर the $LogFile was created on a प्रणाली with a dअगरferent page size to ours
 * yet and mst deprotection would fail अगर our page size is smaller.
 */
bool ntfs_check_logfile(काष्ठा inode *log_vi, RESTART_PAGE_HEADER **rp)
अणु
	s64 size, pos;
	LSN rstr1_lsn, rstr2_lsn;
	ntfs_volume *vol = NTFS_SB(log_vi->i_sb);
	काष्ठा address_space *mapping = log_vi->i_mapping;
	काष्ठा page *page = शून्य;
	u8 *kaddr = शून्य;
	RESTART_PAGE_HEADER *rstr1_ph = शून्य;
	RESTART_PAGE_HEADER *rstr2_ph = शून्य;
	पूर्णांक log_page_size, err;
	bool logfile_is_empty = true;
	u8 log_page_bits;

	ntfs_debug("Entering.");
	/* An empty $LogFile must have been clean beक्रमe it got emptied. */
	अगर (NVolLogFileEmpty(vol))
		जाओ is_empty;
	size = i_size_पढ़ो(log_vi);
	/* Make sure the file करोesn't exceed the maximum allowed size. */
	अगर (size > MaxLogFileSize)
		size = MaxLogFileSize;
	/*
	 * Truncate size to a multiple of the page cache size or the शेष
	 * log page size अगर the page cache size is between the शेष log page
	 * log page size अगर the page cache size is between the शेष log page
	 * size and twice that.
	 */
	अगर (PAGE_SIZE >= DefaultLogPageSize && PAGE_SIZE <=
			DefaultLogPageSize * 2)
		log_page_size = DefaultLogPageSize;
	अन्यथा
		log_page_size = PAGE_SIZE;
	/*
	 * Use ntfs_ffs() instead of ffs() to enable the compiler to
	 * optimize log_page_size and log_page_bits पूर्णांकo स्थिरants.
	 */
	log_page_bits = ntfs_ffs(log_page_size) - 1;
	size &= ~(s64)(log_page_size - 1);
	/*
	 * Ensure the log file is big enough to store at least the two restart
	 * pages and the minimum number of log record pages.
	 */
	अगर (size < log_page_size * 2 || (size - log_page_size * 2) >>
			log_page_bits < MinLogRecordPages) अणु
		ntfs_error(vol->sb, "$LogFile is too small.");
		वापस false;
	पूर्ण
	/*
	 * Read through the file looking क्रम a restart page.  Since the restart
	 * page header is at the beginning of a page we only need to search at
	 * what could be the beginning of a page (क्रम each page size) rather
	 * than scanning the whole file byte by byte.  If all potential places
	 * contain empty and uninitialzed records, the log file can be assumed
	 * to be empty.
	 */
	क्रम (pos = 0; pos < size; pos <<= 1) अणु
		pgoff_t idx = pos >> PAGE_SHIFT;
		अगर (!page || page->index != idx) अणु
			अगर (page)
				ntfs_unmap_page(page);
			page = ntfs_map_page(mapping, idx);
			अगर (IS_ERR(page)) अणु
				ntfs_error(vol->sb, "Error mapping $LogFile "
						"page (index %lu).", idx);
				जाओ err_out;
			पूर्ण
		पूर्ण
		kaddr = (u8*)page_address(page) + (pos & ~PAGE_MASK);
		/*
		 * A non-empty block means the logfile is not empty जबतक an
		 * empty block after a non-empty block has been encountered
		 * means we are करोne.
		 */
		अगर (!ntfs_is_empty_recordp((le32*)kaddr))
			logfile_is_empty = false;
		अन्यथा अगर (!logfile_is_empty)
			अवरोध;
		/*
		 * A log record page means there cannot be a restart page after
		 * this so no need to जारी searching.
		 */
		अगर (ntfs_is_rcrd_recordp((le32*)kaddr))
			अवरोध;
		/* If not a (modअगरied by chkdsk) restart page, जारी. */
		अगर (!ntfs_is_rstr_recordp((le32*)kaddr) &&
				!ntfs_is_chkd_recordp((le32*)kaddr)) अणु
			अगर (!pos)
				pos = NTFS_BLOCK_SIZE >> 1;
			जारी;
		पूर्ण
		/*
		 * Check the (modअगरied by chkdsk) restart page क्रम consistency
		 * and get a copy of the complete multi sector transfer
		 * deरक्षित restart page.
		 */
		err = ntfs_check_and_load_restart_page(log_vi,
				(RESTART_PAGE_HEADER*)kaddr, pos,
				!rstr1_ph ? &rstr1_ph : &rstr2_ph,
				!rstr1_ph ? &rstr1_lsn : &rstr2_lsn);
		अगर (!err) अणु
			/*
			 * If we have now found the first (modअगरied by chkdsk)
			 * restart page, जारी looking क्रम the second one.
			 */
			अगर (!pos) अणु
				pos = NTFS_BLOCK_SIZE >> 1;
				जारी;
			पूर्ण
			/*
			 * We have now found the second (modअगरied by chkdsk)
			 * restart page, so we can stop looking.
			 */
			अवरोध;
		पूर्ण
		/*
		 * Error output alपढ़ोy करोne inside the function.  Note, we करो
		 * not पात अगर the restart page was invalid as we might still
		 * find a valid one further in the file.
		 */
		अगर (err != -EINVAL) अणु
			ntfs_unmap_page(page);
			जाओ err_out;
		पूर्ण
		/* Continue looking. */
		अगर (!pos)
			pos = NTFS_BLOCK_SIZE >> 1;
	पूर्ण
	अगर (page)
		ntfs_unmap_page(page);
	अगर (logfile_is_empty) अणु
		NVolSetLogFileEmpty(vol);
is_empty:
		ntfs_debug("Done.  ($LogFile is empty.)");
		वापस true;
	पूर्ण
	अगर (!rstr1_ph) अणु
		BUG_ON(rstr2_ph);
		ntfs_error(vol->sb, "Did not find any restart pages in "
				"$LogFile and it was not empty.");
		वापस false;
	पूर्ण
	/* If both restart pages were found, use the more recent one. */
	अगर (rstr2_ph) अणु
		/*
		 * If the second restart area is more recent, चयन to it.
		 * Otherwise just throw it away.
		 */
		अगर (rstr2_lsn > rstr1_lsn) अणु
			ntfs_debug("Using second restart page as it is more "
					"recent.");
			ntfs_मुक्त(rstr1_ph);
			rstr1_ph = rstr2_ph;
			/* rstr1_lsn = rstr2_lsn; */
		पूर्ण अन्यथा अणु
			ntfs_debug("Using first restart page as it is more "
					"recent.");
			ntfs_मुक्त(rstr2_ph);
		पूर्ण
		rstr2_ph = शून्य;
	पूर्ण
	/* All consistency checks passed. */
	अगर (rp)
		*rp = rstr1_ph;
	अन्यथा
		ntfs_मुक्त(rstr1_ph);
	ntfs_debug("Done.");
	वापस true;
err_out:
	अगर (rstr1_ph)
		ntfs_मुक्त(rstr1_ph);
	वापस false;
पूर्ण

/**
 * ntfs_is_logfile_clean - check in the journal अगर the volume is clean
 * @log_vi:	काष्ठा inode of loaded journal $LogFile to check
 * @rp:		copy of the current restart page
 *
 * Analyze the $LogFile journal and वापस 'true' अगर it indicates the volume was
 * shutकरोwn cleanly and 'false' अगर not.
 *
 * At present we only look at the two restart pages and ignore the log record
 * pages.  This is a little bit crude in that there will be a very small number
 * of हालs where we think that a volume is dirty when in fact it is clean.
 * This should only affect volumes that have not been shutकरोwn cleanly but did
 * not have any pending, non-check-poपूर्णांकed i/o, i.e. they were completely idle
 * at least क्रम the five seconds preceding the unclean shutकरोwn.
 *
 * This function assumes that the $LogFile journal has alपढ़ोy been consistency
 * checked by a call to ntfs_check_logfile() and in particular अगर the $LogFile
 * is empty this function requires that NVolLogFileEmpty() is true otherwise an
 * empty volume will be reported as dirty.
 */
bool ntfs_is_logfile_clean(काष्ठा inode *log_vi, स्थिर RESTART_PAGE_HEADER *rp)
अणु
	ntfs_volume *vol = NTFS_SB(log_vi->i_sb);
	RESTART_AREA *ra;

	ntfs_debug("Entering.");
	/* An empty $LogFile must have been clean beक्रमe it got emptied. */
	अगर (NVolLogFileEmpty(vol)) अणु
		ntfs_debug("Done.  ($LogFile is empty.)");
		वापस true;
	पूर्ण
	BUG_ON(!rp);
	अगर (!ntfs_is_rstr_record(rp->magic) &&
			!ntfs_is_chkd_record(rp->magic)) अणु
		ntfs_error(vol->sb, "Restart page buffer is invalid.  This is "
				"probably a bug in that the $LogFile should "
				"have been consistency checked before calling "
				"this function.");
		वापस false;
	पूर्ण
	ra = (RESTART_AREA*)((u8*)rp + le16_to_cpu(rp->restart_area_offset));
	/*
	 * If the $LogFile has active clients, i.e. it is खोलो, and we करो not
	 * have the RESTART_VOLUME_IS_CLEAN bit set in the restart area flags,
	 * we assume there was an unclean shutकरोwn.
	 */
	अगर (ra->client_in_use_list != LOGखाता_NO_CLIENT &&
			!(ra->flags & RESTART_VOLUME_IS_CLEAN)) अणु
		ntfs_debug("Done.  $LogFile indicates a dirty shutdown.");
		वापस false;
	पूर्ण
	/* $LogFile indicates a clean shutकरोwn. */
	ntfs_debug("Done.  $LogFile indicates a clean shutdown.");
	वापस true;
पूर्ण

/**
 * ntfs_empty_logfile - empty the contents of the $LogFile journal
 * @log_vi:	काष्ठा inode of loaded journal $LogFile to empty
 *
 * Empty the contents of the $LogFile journal @log_vi and वापस 'true' on
 * success and 'false' on error.
 *
 * This function assumes that the $LogFile journal has alपढ़ोy been consistency
 * checked by a call to ntfs_check_logfile() and that ntfs_is_logfile_clean()
 * has been used to ensure that the $LogFile is clean.
 */
bool ntfs_empty_logfile(काष्ठा inode *log_vi)
अणु
	VCN vcn, end_vcn;
	ntfs_inode *log_ni = NTFS_I(log_vi);
	ntfs_volume *vol = log_ni->vol;
	काष्ठा super_block *sb = vol->sb;
	runlist_element *rl;
	अचिन्हित दीर्घ flags;
	अचिन्हित block_size, block_size_bits;
	पूर्णांक err;
	bool should_रुको = true;

	ntfs_debug("Entering.");
	अगर (NVolLogFileEmpty(vol)) अणु
		ntfs_debug("Done.");
		वापस true;
	पूर्ण
	/*
	 * We cannot use ntfs_attr_set() because we may be still in the middle
	 * of a mount operation.  Thus we करो the emptying by hand by first
	 * zapping the page cache pages क्रम the $LogFile/$DATA attribute and
	 * then emptying each of the buffers in each of the clusters specअगरied
	 * by the runlist by hand.
	 */
	block_size = sb->s_blocksize;
	block_size_bits = sb->s_blocksize_bits;
	vcn = 0;
	पढ़ो_lock_irqsave(&log_ni->size_lock, flags);
	end_vcn = (log_ni->initialized_size + vol->cluster_size_mask) >>
			vol->cluster_size_bits;
	पढ़ो_unlock_irqrestore(&log_ni->size_lock, flags);
	truncate_inode_pages(log_vi->i_mapping, 0);
	करोwn_ग_लिखो(&log_ni->runlist.lock);
	rl = log_ni->runlist.rl;
	अगर (unlikely(!rl || vcn < rl->vcn || !rl->length)) अणु
map_vcn:
		err = ntfs_map_runlist_nolock(log_ni, vcn, शून्य);
		अगर (err) अणु
			ntfs_error(sb, "Failed to map runlist fragment (error "
					"%d).", -err);
			जाओ err;
		पूर्ण
		rl = log_ni->runlist.rl;
		BUG_ON(!rl || vcn < rl->vcn || !rl->length);
	पूर्ण
	/* Seek to the runlist element containing @vcn. */
	जबतक (rl->length && vcn >= rl[1].vcn)
		rl++;
	करो अणु
		LCN lcn;
		sector_t block, end_block;
		s64 len;

		/*
		 * If this run is not mapped map it now and start again as the
		 * runlist will have been updated.
		 */
		lcn = rl->lcn;
		अगर (unlikely(lcn == LCN_RL_NOT_MAPPED)) अणु
			vcn = rl->vcn;
			जाओ map_vcn;
		पूर्ण
		/* If this run is not valid पात with an error. */
		अगर (unlikely(!rl->length || lcn < LCN_HOLE))
			जाओ rl_err;
		/* Skip holes. */
		अगर (lcn == LCN_HOLE)
			जारी;
		block = lcn << vol->cluster_size_bits >> block_size_bits;
		len = rl->length;
		अगर (rl[1].vcn > end_vcn)
			len = end_vcn - rl->vcn;
		end_block = (lcn + len) << vol->cluster_size_bits >>
				block_size_bits;
		/* Iterate over the blocks in the run and empty them. */
		करो अणु
			काष्ठा buffer_head *bh;

			/* Obtain the buffer, possibly not uptodate. */
			bh = sb_getblk(sb, block);
			BUG_ON(!bh);
			/* Setup buffer i/o submission. */
			lock_buffer(bh);
			bh->b_end_io = end_buffer_ग_लिखो_sync;
			get_bh(bh);
			/* Set the entire contents of the buffer to 0xff. */
			स_रखो(bh->b_data, -1, block_size);
			अगर (!buffer_uptodate(bh))
				set_buffer_uptodate(bh);
			अगर (buffer_dirty(bh))
				clear_buffer_dirty(bh);
			/*
			 * Submit the buffer and रुको क्रम i/o to complete but
			 * only क्रम the first buffer so we करो not miss really
			 * serious i/o errors.  Once the first buffer has
			 * completed ignore errors afterwards as we can assume
			 * that अगर one buffer worked all of them will work.
			 */
			submit_bh(REQ_OP_WRITE, 0, bh);
			अगर (should_रुको) अणु
				should_रुको = false;
				रुको_on_buffer(bh);
				अगर (unlikely(!buffer_uptodate(bh)))
					जाओ io_err;
			पूर्ण
			brअन्यथा(bh);
		पूर्ण जबतक (++block < end_block);
	पूर्ण जबतक ((++rl)->vcn < end_vcn);
	up_ग_लिखो(&log_ni->runlist.lock);
	/*
	 * Zap the pages again just in हाल any got instantiated whilst we were
	 * emptying the blocks by hand.  FIXME: We may not have completed
	 * writing to all the buffer heads yet so this may happen too early.
	 * We really should use a kernel thपढ़ो to करो the emptying
	 * asynchronously and then we can also set the volume dirty and output
	 * an error message अगर emptying should fail.
	 */
	truncate_inode_pages(log_vi->i_mapping, 0);
	/* Set the flag so we करो not have to करो it again on remount. */
	NVolSetLogFileEmpty(vol);
	ntfs_debug("Done.");
	वापस true;
io_err:
	ntfs_error(sb, "Failed to write buffer.  Unmount and run chkdsk.");
	जाओ dirty_err;
rl_err:
	ntfs_error(sb, "Runlist is corrupt.  Unmount and run chkdsk.");
dirty_err:
	NVolSetErrors(vol);
	err = -EIO;
err:
	up_ग_लिखो(&log_ni->runlist.lock);
	ntfs_error(sb, "Failed to fill $LogFile with 0xff bytes (error %d).",
			-err);
	वापस false;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */
