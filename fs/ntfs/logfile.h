<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * logfile.h - Defines क्रम NTFS kernel journal ($LogFile) handling.  Part of
 *	       the Linux-NTFS project.
 *
 * Copyright (c) 2000-2005 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_LOGखाता_H
#घोषणा _LINUX_NTFS_LOGखाता_H

#अगर_घोषित NTFS_RW

#समावेश <linux/fs.h>

#समावेश "types.h"
#समावेश "endian.h"
#समावेश "layout.h"

/*
 * Journal ($LogFile) organization:
 *
 * Two restart areas present in the first two pages (restart pages, one restart
 * area in each page).  When the volume is dismounted they should be identical,
 * except क्रम the update sequence array which usually has a dअगरferent update
 * sequence number.
 *
 * These are followed by log records organized in pages headed by a log record
 * header going up to log file size.  Not all pages contain log records when a
 * volume is first क्रमmatted, but as the volume ages, all records will be used.
 * When the log file fills up, the records at the beginning are purged (by
 * modअगरying the oldest_lsn to a higher value presumably) and writing begins
 * at the beginning of the file.  Effectively, the log file is viewed as a
 * circular entity.
 *
 * NOTE: Winकरोws NT, 2000, and XP all use log file version 1.1 but they accept
 * versions <= 1.x, including 0.-1.  (Yes, that is a minus one in there!)  We
 * probably only want to support 1.1 as this seems to be the current version
 * and we करोn't know how that dअगरfers from the older versions.  The only
 * exception is अगर the journal is clean as marked by the two restart pages
 * then it करोesn't matter whether we are on an earlier version.  We can just
 * reinitialize the logfile and start again with version 1.1.
 */

/* Some $LogFile related स्थिरants. */
#घोषणा MaxLogFileSize		0x100000000ULL
#घोषणा DefaultLogPageSize	4096
#घोषणा MinLogRecordPages	48

/*
 * Log file restart page header (begins the restart area).
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0	NTFS_RECORD; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
/*  0*/	NTFS_RECORD_TYPE magic;	/* The magic is "RSTR". */
/*  4*/	le16 usa_ofs;		/* See NTFS_RECORD definition in layout.h.
				   When creating, set this to be immediately
				   after this header काष्ठाure (without any
				   alignment). */
/*  6*/	le16 usa_count;		/* See NTFS_RECORD definition in layout.h. */

/*  8*/	leLSN chkdsk_lsn;	/* The last log file sequence number found by
				   chkdsk.  Only used when the magic is changed
				   to "CHKD".  Otherwise this is zero. */
/* 16*/	le32 प्रणाली_page_size;	/* Byte size of प्रणाली pages when the log file
				   was created, has to be >= 512 and a घातer of
				   2.  Use this to calculate the required size
				   of the usa (usa_count) and add it to usa_ofs.
				   Then verअगरy that the result is less than the
				   value of the restart_area_offset. */
/* 20*/	le32 log_page_size;	/* Byte size of log file pages, has to be >=
				   512 and a घातer of 2.  The शेष is 4096
				   and is used when the प्रणाली page size is
				   between 4096 and 8192.  Otherwise this is
				   set to the प्रणाली page size instead. */
/* 24*/	le16 restart_area_offset;/* Byte offset from the start of this header to
				   the RESTART_AREA.  Value has to be aligned
				   to 8-byte boundary.  When creating, set this
				   to be after the usa. */
/* 26*/	sle16 minor_ver;	/* Log file minor version.  Only check अगर major
				   version is 1. */
/* 28*/	sle16 major_ver;	/* Log file major version.  We only support
				   version 1.1. */
/* माप() = 30 (0x1e) bytes */
पूर्ण __attribute__ ((__packed__)) RESTART_PAGE_HEADER;

/*
 * Constant क्रम the log client indices meaning that there are no client records
 * in this particular client array.  Also inside the client records themselves,
 * this means that there are no client records preceding or following this one.
 */
#घोषणा LOGखाता_NO_CLIENT	cpu_to_le16(0xffff)
#घोषणा LOGखाता_NO_CLIENT_CPU	0xffff

/*
 * These are the so far known RESTART_AREA_* flags (16-bit) which contain
 * inक्रमmation about the log file in which they are present.
 */
क्रमागत अणु
	RESTART_VOLUME_IS_CLEAN	= cpu_to_le16(0x0002),
	RESTART_SPACE_FILLER	= cpu_to_le16(0xffff), /* gcc: Force क्रमागत bit width to 16. */
पूर्ण __attribute__ ((__packed__));

प्रकार le16 RESTART_AREA_FLAGS;

/*
 * Log file restart area record.  The offset of this record is found by adding
 * the offset of the RESTART_PAGE_HEADER to the restart_area_offset value found
 * in it.  See notes at restart_area_offset above.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	leLSN current_lsn;	/* The current, i.e. last LSN inside the log
				   when the restart area was last written.
				   This happens often but what is the पूर्णांकerval?
				   Is it just fixed समय or is it every समय a
				   check poपूर्णांक is written or somethine अन्यथा?
				   On create set to 0. */
/*  8*/	le16 log_clients;	/* Number of log client records in the array of
				   log client records which follows this
				   restart area.  Must be 1.  */
/* 10*/	le16 client_मुक्त_list;	/* The index of the first मुक्त log client record
				   in the array of log client records.
				   LOGखाता_NO_CLIENT means that there are no
				   मुक्त log client records in the array.
				   If != LOGखाता_NO_CLIENT, check that
				   log_clients > client_मुक्त_list.  On Win2k
				   and presumably earlier, on a clean volume
				   this is != LOGखाता_NO_CLIENT, and it should
				   be 0, i.e. the first (and only) client
				   record is मुक्त and thus the logfile is
				   बंदd and hence clean.  A dirty volume
				   would have left the logfile खोलो and hence
				   this would be LOGखाता_NO_CLIENT.  On WinXP
				   and presumably later, the logfile is always
				   खोलो, even on clean shutकरोwn so this should
				   always be LOGखाता_NO_CLIENT. */
/* 12*/	le16 client_in_use_list;/* The index of the first in-use log client
				   record in the array of log client records.
				   LOGखाता_NO_CLIENT means that there are no
				   in-use log client records in the array.  If
				   != LOGखाता_NO_CLIENT check that log_clients
				   > client_in_use_list.  On Win2k and
				   presumably earlier, on a clean volume this
				   is LOGखाता_NO_CLIENT, i.e. there are no
				   client records in use and thus the logfile
				   is बंदd and hence clean.  A dirty volume
				   would have left the logfile खोलो and hence
				   this would be != LOGखाता_NO_CLIENT, and it
				   should be 0, i.e. the first (and only)
				   client record is in use.  On WinXP and
				   presumably later, the logfile is always
				   खोलो, even on clean shutकरोwn so this should
				   always be 0. */
/* 14*/	RESTART_AREA_FLAGS flags;/* Flags modअगरying LFS behaviour.  On Win2k
				   and presumably earlier this is always 0.  On
				   WinXP and presumably later, अगर the logfile
				   was shutकरोwn cleanly, the second bit,
				   RESTART_VOLUME_IS_CLEAN, is set.  This bit
				   is cleared when the volume is mounted by
				   WinXP and set when the volume is dismounted,
				   thus अगर the logfile is dirty, this bit is
				   clear.  Thus we करोn't need to check the
				   Winकरोws version to determine अगर the logfile
				   is clean.  Instead अगर the logfile is बंदd,
				   we know it must be clean.  If it is खोलो and
				   this bit is set, we also know it must be
				   clean.  If on the other hand the logfile is
				   खोलो and this bit is clear, we can be almost
				   certain that the logfile is dirty. */
/* 16*/	le32 seq_number_bits;	/* How many bits to use क्रम the sequence
				   number.  This is calculated as 67 - the
				   number of bits required to store the logfile
				   size in bytes and this can be used in with
				   the specअगरied file_size as a consistency
				   check. */
/* 20*/	le16 restart_area_length;/* Length of the restart area including the
				   client array.  Following checks required अगर
				   version matches.  Otherwise, skip them.
				   restart_area_offset + restart_area_length
				   has to be <= प्रणाली_page_size.  Also,
				   restart_area_length has to be >=
				   client_array_offset + (log_clients *
				   माप(log client record)). */
/* 22*/	le16 client_array_offset;/* Offset from the start of this record to
				   the first log client record अगर versions are
				   matched.  When creating, set this to be
				   after this restart area काष्ठाure, aligned
				   to 8-bytes boundary.  If the versions करो not
				   match, this is ignored and the offset is
				   assumed to be (माप(RESTART_AREA) + 7) &
				   ~7, i.e. rounded up to first 8-byte
				   boundary.  Either way, client_array_offset
				   has to be aligned to an 8-byte boundary.
				   Also, restart_area_offset +
				   client_array_offset has to be <= 510.
				   Finally, client_array_offset + (log_clients
				   * माप(log client record)) has to be <=
				   प्रणाली_page_size.  On Win2k and presumably
				   earlier, this is 0x30, i.e. immediately
				   following this record.  On WinXP and
				   presumably later, this is 0x40, i.e. there
				   are 16 extra bytes between this record and
				   the client array.  This probably means that
				   the RESTART_AREA record is actually bigger
				   in WinXP and later. */
/* 24*/	sle64 file_size;	/* Usable byte size of the log file.  If the
				   restart_area_offset + the offset of the
				   file_size are > 510 then corruption has
				   occurred.  This is the very first check when
				   starting with the restart_area as अगर it
				   fails it means that some of the above values
				   will be corrupted by the multi sector
				   transfer protection.  The file_size has to
				   be rounded करोwn to be a multiple of the
				   log_page_size in the RESTART_PAGE_HEADER and
				   then it has to be at least big enough to
				   store the two restart pages and 48 (0x30)
				   log record pages. */
/* 32*/	le32 last_lsn_data_length;/* Length of data of last LSN, not including
				   the log record header.  On create set to
				   0. */
/* 36*/	le16 log_record_header_length;/* Byte size of the log record header.
				   If the version matches then check that the
				   value of log_record_header_length is a
				   multiple of 8, i.e.
				   (log_record_header_length + 7) & ~7 ==
				   log_record_header_length.  When creating set
				   it to माप(LOG_RECORD_HEADER), aligned to
				   8 bytes. */
/* 38*/	le16 log_page_data_offset;/* Offset to the start of data in a log record
				   page.  Must be a multiple of 8.  On create
				   set it to immediately after the update
				   sequence array of the log record page. */
/* 40*/	le32 restart_log_खोलो_count;/* A counter that माला_लो incremented every
				   समय the logfile is restarted which happens
				   at mount समय when the logfile is खोलोed.
				   When creating set to a अक्रमom value.  Win2k
				   sets it to the low 32 bits of the current
				   प्रणाली समय in NTFS क्रमmat (see समय.स). */
/* 44*/	le32 reserved;		/* Reserved/alignment to 8-byte boundary. */
/* माप() = 48 (0x30) bytes */
पूर्ण __attribute__ ((__packed__)) RESTART_AREA;

/*
 * Log client record.  The offset of this record is found by adding the offset
 * of the RESTART_AREA to the client_array_offset value found in it.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	leLSN oldest_lsn;	/* Oldest LSN needed by this client.  On create
				   set to 0. */
/*  8*/	leLSN client_restart_lsn;/* LSN at which this client needs to restart
				   the volume, i.e. the current position within
				   the log file.  At present, अगर clean this
				   should = current_lsn in restart area but it
				   probably also = current_lsn when dirty most
				   of the समय.  At create set to 0. */
/* 16*/	le16 prev_client;	/* The offset to the previous log client record
				   in the array of log client records.
				   LOGखाता_NO_CLIENT means there is no previous
				   client record, i.e. this is the first one.
				   This is always LOGखाता_NO_CLIENT. */
/* 18*/	le16 next_client;	/* The offset to the next log client record in
				   the array of log client records.
				   LOGखाता_NO_CLIENT means there are no next
				   client records, i.e. this is the last one.
				   This is always LOGखाता_NO_CLIENT. */
/* 20*/	le16 seq_number;	/* On Win2k and presumably earlier, this is set
				   to zero every समय the logfile is restarted
				   and it is incremented when the logfile is
				   बंदd at dismount समय.  Thus it is 0 when
				   dirty and 1 when clean.  On WinXP and
				   presumably later, this is always 0. */
/* 22*/	u8 reserved[6];		/* Reserved/alignment. */
/* 28*/	le32 client_name_length;/* Length of client name in bytes.  Should
				   always be 8. */
/* 32*/	ntfsअक्षर client_name[64];/* Name of the client in Unicode.  Should
				   always be "NTFS" with the reमुख्यing bytes
				   set to 0. */
/* माप() = 160 (0xa0) bytes */
पूर्ण __attribute__ ((__packed__)) LOG_CLIENT_RECORD;

बाह्य bool ntfs_check_logfile(काष्ठा inode *log_vi,
		RESTART_PAGE_HEADER **rp);

बाह्य bool ntfs_is_logfile_clean(काष्ठा inode *log_vi,
		स्थिर RESTART_PAGE_HEADER *rp);

बाह्य bool ntfs_empty_logfile(काष्ठा inode *log_vi);

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* _LINUX_NTFS_LOGखाता_H */
