<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * layout.h - All NTFS associated on-disk काष्ठाures. Part of the Linux-NTFS
 *	      project.
 *
 * Copyright (c) 2001-2005 Anton Altaparmakov
 * Copyright (c) 2002 Riअक्षरd Russon
 */

#अगर_अघोषित _LINUX_NTFS_LAYOUT_H
#घोषणा _LINUX_NTFS_LAYOUT_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <यंत्र/byteorder.h>

#समावेश "types.h"

/* The NTFS oem_id "NTFS    " */
#घोषणा magicNTFS	cpu_to_le64(0x202020205346544eULL)

/*
 * Location of bootsector on partition:
 *	The standard NTFS_BOOT_SECTOR is on sector 0 of the partition.
 *	On NT4 and above there is one backup copy of the boot sector to
 *	be found on the last sector of the partition (not normally accessible
 *	from within Winकरोws as the bootsector contained number of sectors
 *	value is one less than the actual value!).
 *	On versions of NT 3.51 and earlier, the backup copy was located at
 *	number of sectors/2 (पूर्णांकeger भागide), i.e. in the middle of the volume.
 */

/*
 * BIOS parameter block (bpb) काष्ठाure.
 */
प्रकार काष्ठा अणु
	le16 bytes_per_sector;		/* Size of a sector in bytes. */
	u8  sectors_per_cluster;	/* Size of a cluster in sectors. */
	le16 reserved_sectors;		/* zero */
	u8  fats;			/* zero */
	le16 root_entries;		/* zero */
	le16 sectors;			/* zero */
	u8  media_type;			/* 0xf8 = hard disk */
	le16 sectors_per_fat;		/* zero */
	le16 sectors_per_track;		/* irrelevant */
	le16 heads;			/* irrelevant */
	le32 hidden_sectors;		/* zero */
	le32 large_sectors;		/* zero */
पूर्ण __attribute__ ((__packed__)) BIOS_PARAMETER_BLOCK;

/*
 * NTFS boot sector काष्ठाure.
 */
प्रकार काष्ठा अणु
	u8  jump[3];			/* Irrelevant (jump to boot up code).*/
	le64 oem_id;			/* Magic "NTFS    ". */
	BIOS_PARAMETER_BLOCK bpb;	/* See BIOS_PARAMETER_BLOCK. */
	u8  unused[4];			/* zero, NTFS diskedit.exe states that
					   this is actually:
						__u8 physical_drive;	// 0x80
						__u8 current_head;	// zero
						__u8 extended_boot_signature;
									// 0x80
						__u8 unused;		// zero
					 */
/*0x28*/sle64 number_of_sectors;	/* Number of sectors in volume. Gives
					   maximum volume size of 2^63 sectors.
					   Assuming standard sector size of 512
					   bytes, the maximum byte size is
					   approx. 4.7x10^21 bytes. (-; */
	sle64 mft_lcn;			/* Cluster location of mft data. */
	sle64 mfपंचांगirr_lcn;		/* Cluster location of copy of mft. */
	s8  clusters_per_mft_record;	/* Mft record size in clusters. */
	u8  reserved0[3];		/* zero */
	s8  clusters_per_index_record;	/* Index block size in clusters. */
	u8  reserved1[3];		/* zero */
	le64 volume_serial_number;	/* Irrelevant (serial number). */
	le32 checksum;			/* Boot sector checksum. */
/*0x54*/u8  bootstrap[426];		/* Irrelevant (boot up code). */
	le16 end_of_sector_marker;	/* End of bootsector magic. Always is
					   0xaa55 in little endian. */
/* माप() = 512 (0x200) bytes */
पूर्ण __attribute__ ((__packed__)) NTFS_BOOT_SECTOR;

/*
 * Magic identअगरiers present at the beginning of all ntfs record containing
 * records (like mft records क्रम example).
 */
क्रमागत अणु
	/* Found in $MFT/$DATA. */
	magic_खाता = cpu_to_le32(0x454c4946), /* Mft entry. */
	magic_INDX = cpu_to_le32(0x58444e49), /* Index buffer. */
	magic_HOLE = cpu_to_le32(0x454c4f48), /* ? (NTFS 3.0+?) */

	/* Found in $LogFile/$DATA. */
	magic_RSTR = cpu_to_le32(0x52545352), /* Restart page. */
	magic_RCRD = cpu_to_le32(0x44524352), /* Log record page. */

	/* Found in $LogFile/$DATA.  (May be found in $MFT/$DATA, also?) */
	magic_CHKD = cpu_to_le32(0x444b4843), /* Modअगरied by chkdsk. */

	/* Found in all ntfs record containing records. */
	magic_BAAD = cpu_to_le32(0x44414142), /* Failed multi sector
						       transfer was detected. */
	/*
	 * Found in $LogFile/$DATA when a page is full of 0xff bytes and is
	 * thus not initialized.  Page must be initialized beक्रमe using it.
	 */
	magic_empty = cpu_to_le32(0xffffffff) /* Record is empty. */
पूर्ण;

प्रकार le32 NTFS_RECORD_TYPE;

/*
 * Generic magic comparison macros. Finally found a use क्रम the ## preprocessor
 * चालक! (-8
 */

अटल अंतरभूत bool __ntfs_is_magic(le32 x, NTFS_RECORD_TYPE r)
अणु
	वापस (x == r);
पूर्ण
#घोषणा ntfs_is_magic(x, m)	__ntfs_is_magic(x, magic_##m)

अटल अंतरभूत bool __ntfs_is_magicp(le32 *p, NTFS_RECORD_TYPE r)
अणु
	वापस (*p == r);
पूर्ण
#घोषणा ntfs_is_magicp(p, m)	__ntfs_is_magicp(p, magic_##m)

/*
 * Specialised magic comparison macros क्रम the NTFS_RECORD_TYPEs defined above.
 */
#घोषणा ntfs_is_file_record(x)		( ntfs_is_magic (x, खाता) )
#घोषणा ntfs_is_file_recordp(p)		( ntfs_is_magicp(p, खाता) )
#घोषणा ntfs_is_mft_record(x)		( ntfs_is_file_record (x) )
#घोषणा ntfs_is_mft_recordp(p)		( ntfs_is_file_recordp(p) )
#घोषणा ntfs_is_indx_record(x)		( ntfs_is_magic (x, INDX) )
#घोषणा ntfs_is_indx_recordp(p)		( ntfs_is_magicp(p, INDX) )
#घोषणा ntfs_is_hole_record(x)		( ntfs_is_magic (x, HOLE) )
#घोषणा ntfs_is_hole_recordp(p)		( ntfs_is_magicp(p, HOLE) )

#घोषणा ntfs_is_rstr_record(x)		( ntfs_is_magic (x, RSTR) )
#घोषणा ntfs_is_rstr_recordp(p)		( ntfs_is_magicp(p, RSTR) )
#घोषणा ntfs_is_rcrd_record(x)		( ntfs_is_magic (x, RCRD) )
#घोषणा ntfs_is_rcrd_recordp(p)		( ntfs_is_magicp(p, RCRD) )

#घोषणा ntfs_is_chkd_record(x)		( ntfs_is_magic (x, CHKD) )
#घोषणा ntfs_is_chkd_recordp(p)		( ntfs_is_magicp(p, CHKD) )

#घोषणा ntfs_is_baad_record(x)		( ntfs_is_magic (x, BAAD) )
#घोषणा ntfs_is_baad_recordp(p)		( ntfs_is_magicp(p, BAAD) )

#घोषणा ntfs_is_empty_record(x)		( ntfs_is_magic (x, empty) )
#घोषणा ntfs_is_empty_recordp(p)	( ntfs_is_magicp(p, empty) )

/*
 * The Update Sequence Array (usa) is an array of the le16 values which beदीर्घ
 * to the end of each sector रक्षित by the update sequence record in which
 * this array is contained. Note that the first entry is the Update Sequence
 * Number (usn), a cyclic counter of how many बार the रक्षित record has
 * been written to disk. The values 0 and -1 (ie. 0xffff) are not used. All
 * last le16's of each sector have to be equal to the usn (during पढ़ोing) or
 * are set to it (during writing). If they are not, an incomplete multi sector
 * transfer has occurred when the data was written.
 * The maximum size क्रम the update sequence array is fixed to:
 *	maximum size = usa_ofs + (usa_count * 2) = 510 bytes
 * The 510 bytes comes from the fact that the last le16 in the array has to
 * (obviously) finish beक्रमe the last le16 of the first 512-byte sector.
 * This क्रमmula can be used as a consistency check in that usa_ofs +
 * (usa_count * 2) has to be less than or equal to 510.
 */
प्रकार काष्ठा अणु
	NTFS_RECORD_TYPE magic;	/* A four-byte magic identअगरying the record
				   type and/or status. */
	le16 usa_ofs;		/* Offset to the Update Sequence Array (usa)
				   from the start of the ntfs record. */
	le16 usa_count;		/* Number of le16 sized entries in the usa
				   including the Update Sequence Number (usn),
				   thus the number of fixups is the usa_count
				   minus 1. */
पूर्ण __attribute__ ((__packed__)) NTFS_RECORD;

/*
 * System files mft record numbers. All these files are always marked as used
 * in the biपंचांगap attribute of the mft; presumably in order to aव्योम accidental
 * allocation क्रम अक्रमom other mft records. Also, the sequence number क्रम each
 * of the प्रणाली files is always equal to their mft record number and it is
 * never modअगरied.
 */
प्रकार क्रमागत अणु
	खाता_MFT       = 0,	/* Master file table (mft). Data attribute
				   contains the entries and biपंचांगap attribute
				   records which ones are in use (bit==1). */
	खाता_MFTMirr   = 1,	/* Mft mirror: copy of first four mft records
				   in data attribute. If cluster size > 4kiB,
				   copy of first N mft records, with
					N = cluster_size / mft_record_size. */
	खाता_LogFile   = 2,	/* Journalling log in data attribute. */
	खाता_Volume    = 3,	/* Volume name attribute and volume inक्रमmation
				   attribute (flags and ntfs version). Winकरोws
				   refers to this file as volume DASD (Direct
				   Access Storage Device). */
	खाता_AttrDef   = 4,	/* Array of attribute definitions in data
				   attribute. */
	खाता_root      = 5,	/* Root directory. */
	खाता_Biपंचांगap    = 6,	/* Allocation biपंचांगap of all clusters (lcns) in
				   data attribute. */
	खाता_Boot      = 7,	/* Boot sector (always at cluster 0) in data
				   attribute. */
	खाता_BadClus   = 8,	/* Contains all bad clusters in the non-resident
				   data attribute. */
	खाता_Secure    = 9,	/* Shared security descriptors in data attribute
				   and two indexes पूर्णांकo the descriptors.
				   Appeared in Winकरोws 2000. Beक्रमe that, this
				   file was named $Quota but was unused. */
	खाता_UpCase    = 10,	/* Upperहाल equivalents of all 65536 Unicode
				   अक्षरacters in data attribute. */
	खाता_Extend    = 11,	/* Directory containing other प्रणाली files (eg.
				   $ObjId, $Quota, $Reparse and $UsnJrnl). This
				   is new to NTFS3.0. */
	खाता_reserved12 = 12,	/* Reserved क्रम future use (records 12-15). */
	खाता_reserved13 = 13,
	खाता_reserved14 = 14,
	खाता_reserved15 = 15,
	खाता_first_user = 16,	/* First user file, used as test limit क्रम
				   whether to allow खोलोing a file or not. */
पूर्ण NTFS_SYSTEM_खाताS;

/*
 * These are the so far known MFT_RECORD_* flags (16-bit) which contain
 * inक्रमmation about the mft record in which they are present.
 */
क्रमागत अणु
	MFT_RECORD_IN_USE	= cpu_to_le16(0x0001),
	MFT_RECORD_IS_सूचीECTORY = cpu_to_le16(0x0002),
पूर्ण __attribute__ ((__packed__));

प्रकार le16 MFT_RECORD_FLAGS;

/*
 * mft references (aka file references or file record segment references) are
 * used whenever a काष्ठाure needs to refer to a record in the mft.
 *
 * A reference consists of a 48-bit index पूर्णांकo the mft and a 16-bit sequence
 * number used to detect stale references.
 *
 * For error reporting purposes we treat the 48-bit index as a चिन्हित quantity.
 *
 * The sequence number is a circular counter (skipping 0) describing how many
 * बार the referenced mft record has been (re)used. This has to match the
 * sequence number of the mft record being referenced, otherwise the reference
 * is considered stale and हटाओd (FIXME: only ntfsck or the driver itself?).
 *
 * If the sequence number is zero it is assumed that no sequence number
 * consistency checking should be perक्रमmed.
 *
 * FIXME: Since inodes are 32-bit as of now, the driver needs to always check
 * क्रम high_part being 0 and अगर not either BUG(), cause a panic() or handle
 * the situation in some other way. This shouldn't be a problem as a volume has
 * to become HUGE in order to need more than 32-bits worth of mft records.
 * Assuming the standard mft record size of 1kb only the records (never mind
 * the non-resident attributes, etc.) would require 4Tb of space on their own
 * क्रम the first 32 bits worth of records. This is only अगर some strange person
 * करोesn't decide to foul play and make the mft sparse which would be a really
 * horrible thing to करो as it would trash our current driver implementation. )-:
 * Do I hear screams "we want 64-bit inodes!" ?!? (-;
 *
 * FIXME: The mft zone is defined as the first 12% of the volume. This space is
 * reserved so that the mft can grow contiguously and hence करोesn't become
 * fragmented. Volume मुक्त space includes the empty part of the mft zone and
 * when the volume's मुक्त 88% are used up, the mft zone is shrunk by a factor
 * of 2, thus making more space available क्रम more files/data. This process is
 * repeated every समय there is no more मुक्त space except क्रम the mft zone until
 * there really is no more मुक्त space.
 */

/*
 * Typedef the MFT_REF as a 64-bit value क्रम easier handling.
 * Also define two unpacking macros to get to the reference (MREF) and
 * sequence number (MSEQNO) respectively.
 * The _LE versions are to be applied on little endian MFT_REFs.
 * Note: The _LE versions will वापस a CPU endian क्रमmatted value!
 */
#घोषणा MFT_REF_MASK_CPU 0x0000ffffffffffffULL
#घोषणा MFT_REF_MASK_LE cpu_to_le64(MFT_REF_MASK_CPU)

प्रकार u64 MFT_REF;
प्रकार le64 leMFT_REF;

#घोषणा MK_MREF(m, s)	((MFT_REF)(((MFT_REF)(s) << 48) |		\
					((MFT_REF)(m) & MFT_REF_MASK_CPU)))
#घोषणा MK_LE_MREF(m, s) cpu_to_le64(MK_MREF(m, s))

#घोषणा MREF(x)		((अचिन्हित दीर्घ)((x) & MFT_REF_MASK_CPU))
#घोषणा MSEQNO(x)	((u16)(((x) >> 48) & 0xffff))
#घोषणा MREF_LE(x)	((अचिन्हित दीर्घ)(le64_to_cpu(x) & MFT_REF_MASK_CPU))
#घोषणा MSEQNO_LE(x)	((u16)((le64_to_cpu(x) >> 48) & 0xffff))

#घोषणा IS_ERR_MREF(x)	(((x) & 0x0000800000000000ULL) ? true : false)
#घोषणा ERR_MREF(x)	((u64)((s64)(x)))
#घोषणा MREF_ERR(x)	((पूर्णांक)((s64)(x)))

/*
 * The mft record header present at the beginning of every record in the mft.
 * This is followed by a sequence of variable length attribute records which
 * is terminated by an attribute of type AT_END which is a truncated attribute
 * in that it only consists of the attribute type code AT_END and none of the
 * other members of the attribute काष्ठाure are present.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0	NTFS_RECORD; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
	NTFS_RECORD_TYPE magic;	/* Usually the magic is "FILE". */
	le16 usa_ofs;		/* See NTFS_RECORD definition above. */
	le16 usa_count;		/* See NTFS_RECORD definition above. */

/*  8*/	le64 lsn;		/* $LogFile sequence number क्रम this record.
				   Changed every समय the record is modअगरied. */
/* 16*/	le16 sequence_number;	/* Number of बार this mft record has been
				   reused. (See description क्रम MFT_REF
				   above.) NOTE: The increment (skipping zero)
				   is करोne when the file is deleted. NOTE: If
				   this is zero it is left zero. */
/* 18*/	le16 link_count;	/* Number of hard links, i.e. the number of
				   directory entries referencing this record.
				   NOTE: Only used in mft base records.
				   NOTE: When deleting a directory entry we
				   check the link_count and अगर it is 1 we
				   delete the file. Otherwise we delete the
				   खाता_NAME_ATTR being referenced by the
				   directory entry from the mft record and
				   decrement the link_count.
				   FIXME: Careful with Win32 + DOS names! */
/* 20*/	le16 attrs_offset;	/* Byte offset to the first attribute in this
				   mft record from the start of the mft record.
				   NOTE: Must be aligned to 8-byte boundary. */
/* 22*/	MFT_RECORD_FLAGS flags;	/* Bit array of MFT_RECORD_FLAGS. When a file
				   is deleted, the MFT_RECORD_IN_USE flag is
				   set to zero. */
/* 24*/	le32 bytes_in_use;	/* Number of bytes used in this mft record.
				   NOTE: Must be aligned to 8-byte boundary. */
/* 28*/	le32 bytes_allocated;	/* Number of bytes allocated क्रम this mft
				   record. This should be equal to the mft
				   record size. */
/* 32*/	leMFT_REF base_mft_record;/* This is zero क्रम base mft records.
				   When it is not zero it is a mft reference
				   poपूर्णांकing to the base mft record to which
				   this record beदीर्घs (this is then used to
				   locate the attribute list attribute present
				   in the base record which describes this
				   extension record and hence might need
				   modअगरication when the extension record
				   itself is modअगरied, also locating the
				   attribute list also means finding the other
				   potential extents, beदीर्घing to the non-base
				   mft record). */
/* 40*/	le16 next_attr_instance;/* The instance number that will be asचिन्हित to
				   the next attribute added to this mft record.
				   NOTE: Incremented each समय after it is used.
				   NOTE: Every समय the mft record is reused
				   this number is set to zero.  NOTE: The first
				   instance number is always 0. */
/* The below fields are specअगरic to NTFS 3.1+ (Winकरोws XP and above): */
/* 42*/ le16 reserved;		/* Reserved/alignment. */
/* 44*/ le32 mft_record_number;	/* Number of this mft record. */
/* माप() = 48 bytes */
/*
 * When (re)using the mft record, we place the update sequence array at this
 * offset, i.e. beक्रमe we start with the attributes.  This also makes sense,
 * otherwise we could run पूर्णांकo problems with the update sequence array
 * containing in itself the last two bytes of a sector which would mean that
 * multi sector transfer protection wouldn't work.  As you can't protect data
 * by overwriting it since you then can't get it back...
 * When पढ़ोing we obviously use the data from the ntfs record header.
 */
पूर्ण __attribute__ ((__packed__)) MFT_RECORD;

/* This is the version without the NTFS 3.1+ specअगरic fields. */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0	NTFS_RECORD; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
	NTFS_RECORD_TYPE magic;	/* Usually the magic is "FILE". */
	le16 usa_ofs;		/* See NTFS_RECORD definition above. */
	le16 usa_count;		/* See NTFS_RECORD definition above. */

/*  8*/	le64 lsn;		/* $LogFile sequence number क्रम this record.
				   Changed every समय the record is modअगरied. */
/* 16*/	le16 sequence_number;	/* Number of बार this mft record has been
				   reused. (See description क्रम MFT_REF
				   above.) NOTE: The increment (skipping zero)
				   is करोne when the file is deleted. NOTE: If
				   this is zero it is left zero. */
/* 18*/	le16 link_count;	/* Number of hard links, i.e. the number of
				   directory entries referencing this record.
				   NOTE: Only used in mft base records.
				   NOTE: When deleting a directory entry we
				   check the link_count and अगर it is 1 we
				   delete the file. Otherwise we delete the
				   खाता_NAME_ATTR being referenced by the
				   directory entry from the mft record and
				   decrement the link_count.
				   FIXME: Careful with Win32 + DOS names! */
/* 20*/	le16 attrs_offset;	/* Byte offset to the first attribute in this
				   mft record from the start of the mft record.
				   NOTE: Must be aligned to 8-byte boundary. */
/* 22*/	MFT_RECORD_FLAGS flags;	/* Bit array of MFT_RECORD_FLAGS. When a file
				   is deleted, the MFT_RECORD_IN_USE flag is
				   set to zero. */
/* 24*/	le32 bytes_in_use;	/* Number of bytes used in this mft record.
				   NOTE: Must be aligned to 8-byte boundary. */
/* 28*/	le32 bytes_allocated;	/* Number of bytes allocated क्रम this mft
				   record. This should be equal to the mft
				   record size. */
/* 32*/	leMFT_REF base_mft_record;/* This is zero क्रम base mft records.
				   When it is not zero it is a mft reference
				   poपूर्णांकing to the base mft record to which
				   this record beदीर्घs (this is then used to
				   locate the attribute list attribute present
				   in the base record which describes this
				   extension record and hence might need
				   modअगरication when the extension record
				   itself is modअगरied, also locating the
				   attribute list also means finding the other
				   potential extents, beदीर्घing to the non-base
				   mft record). */
/* 40*/	le16 next_attr_instance;/* The instance number that will be asचिन्हित to
				   the next attribute added to this mft record.
				   NOTE: Incremented each समय after it is used.
				   NOTE: Every समय the mft record is reused
				   this number is set to zero.  NOTE: The first
				   instance number is always 0. */
/* माप() = 42 bytes */
/*
 * When (re)using the mft record, we place the update sequence array at this
 * offset, i.e. beक्रमe we start with the attributes.  This also makes sense,
 * otherwise we could run पूर्णांकo problems with the update sequence array
 * containing in itself the last two bytes of a sector which would mean that
 * multi sector transfer protection wouldn't work.  As you can't protect data
 * by overwriting it since you then can't get it back...
 * When पढ़ोing we obviously use the data from the ntfs record header.
 */
पूर्ण __attribute__ ((__packed__)) MFT_RECORD_OLD;

/*
 * System defined attributes (32-bit).  Each attribute type has a corresponding
 * attribute name (Unicode string of maximum 64 अक्षरacter length) as described
 * by the attribute definitions present in the data attribute of the $AttrDef
 * प्रणाली file.  On NTFS 3.0 volumes the names are just as the types are named
 * in the below defines exchanging AT_ क्रम the करोllar sign ($).  If that is not
 * a revealing choice of symbol I करो not know what is... (-;
 */
क्रमागत अणु
	AT_UNUSED			= cpu_to_le32(         0),
	AT_STANDARD_INFORMATION		= cpu_to_le32(      0x10),
	AT_ATTRIBUTE_LIST		= cpu_to_le32(      0x20),
	AT_खाता_NAME			= cpu_to_le32(      0x30),
	AT_OBJECT_ID			= cpu_to_le32(      0x40),
	AT_SECURITY_DESCRIPTOR		= cpu_to_le32(      0x50),
	AT_VOLUME_NAME			= cpu_to_le32(      0x60),
	AT_VOLUME_INFORMATION		= cpu_to_le32(      0x70),
	AT_DATA				= cpu_to_le32(      0x80),
	AT_INDEX_ROOT			= cpu_to_le32(      0x90),
	AT_INDEX_ALLOCATION		= cpu_to_le32(      0xa0),
	AT_BITMAP			= cpu_to_le32(      0xb0),
	AT_REPARSE_POINT		= cpu_to_le32(      0xc0),
	AT_EA_INFORMATION		= cpu_to_le32(      0xd0),
	AT_EA				= cpu_to_le32(      0xe0),
	AT_PROPERTY_SET			= cpu_to_le32(      0xf0),
	AT_LOGGED_UTILITY_STREAM	= cpu_to_le32(     0x100),
	AT_FIRST_USER_DEFINED_ATTRIBUTE	= cpu_to_le32(    0x1000),
	AT_END				= cpu_to_le32(0xffffffff)
पूर्ण;

प्रकार le32 ATTR_TYPE;

/*
 * The collation rules क्रम sorting views/indexes/etc (32-bit).
 *
 * COLLATION_BINARY - Collate by binary compare where the first byte is most
 *	signअगरicant.
 * COLLATION_UNICODE_STRING - Collate Unicode strings by comparing their binary
 *	Unicode values, except that when a अक्षरacter can be upperहालd, the
 *	upper हाल value collates beक्रमe the lower हाल one.
 * COLLATION_खाता_NAME - Collate file names as Unicode strings. The collation
 *	is करोne very much like COLLATION_UNICODE_STRING. In fact I have no idea
 *	what the dअगरference is. Perhaps the dअगरference is that file names
 *	would treat some special अक्षरacters in an odd way (see
 *	unistr.c::ntfs_collate_names() and unistr.c::legal_ansi_अक्षर_array[]
 *	क्रम what I mean but COLLATION_UNICODE_STRING would not give any special
 *	treaपंचांगent to any अक्षरacters at all, but this is speculation.
 * COLLATION_NTOFS_ULONG - Sorting is करोne according to ascending le32 key
 *	values. E.g. used क्रम $SII index in खाता_Secure, which sorts by
 *	security_id (le32).
 * COLLATION_NTOFS_SID - Sorting is करोne according to ascending SID values.
 *	E.g. used क्रम $O index in खाता_Extend/$Quota.
 * COLLATION_NTOFS_SECURITY_HASH - Sorting is करोne first by ascending hash
 *	values and second by ascending security_id values. E.g. used क्रम $SDH
 *	index in खाता_Secure.
 * COLLATION_NTOFS_ULONGS - Sorting is करोne according to a sequence of ascending
 *	le32 key values. E.g. used क्रम $O index in खाता_Extend/$ObjId, which
 *	sorts by object_id (16-byte), by splitting up the object_id in four
 *	le32 values and using them as inभागidual keys. E.g. take the following
 *	two security_ids, stored as follows on disk:
 *		1st: a1 61 65 b7 65 7b d4 11 9e 3d 00 e0 81 10 42 59
 *		2nd: 38 14 37 d2 d2 f3 d4 11 a5 21 c8 6b 79 b1 97 45
 *	To compare them, they are split पूर्णांकo four le32 values each, like so:
 *		1st: 0xb76561a1 0x11d47b65 0xe0003d9e 0x59421081
 *		2nd: 0xd2371438 0x11d4f3d2 0x6bc821a5 0x4597b179
 *	Now, it is apparent why the 2nd object_id collates after the 1st: the
 *	first le32 value of the 1st object_id is less than the first le32 of
 *	the 2nd object_id. If the first le32 values of both object_ids were
 *	equal then the second le32 values would be compared, etc.
 */
क्रमागत अणु
	COLLATION_BINARY		= cpu_to_le32(0x00),
	COLLATION_खाता_NAME		= cpu_to_le32(0x01),
	COLLATION_UNICODE_STRING	= cpu_to_le32(0x02),
	COLLATION_NTOFS_ULONG		= cpu_to_le32(0x10),
	COLLATION_NTOFS_SID		= cpu_to_le32(0x11),
	COLLATION_NTOFS_SECURITY_HASH	= cpu_to_le32(0x12),
	COLLATION_NTOFS_ULONGS		= cpu_to_le32(0x13),
पूर्ण;

प्रकार le32 COLLATION_RULE;

/*
 * The flags (32-bit) describing attribute properties in the attribute
 * definition काष्ठाure.  FIXME: This inक्रमmation is based on Regis's
 * inक्रमmation and, according to him, it is not certain and probably
 * incomplete.  The INDEXABLE flag is fairly certainly correct as only the file
 * name attribute has this flag set and this is the only attribute indexed in
 * NT4.
 */
क्रमागत अणु
	ATTR_DEF_INDEXABLE	= cpu_to_le32(0x02), /* Attribute can be
					indexed. */
	ATTR_DEF_MULTIPLE	= cpu_to_le32(0x04), /* Attribute type
					can be present multiple बार in the
					mft records of an inode. */
	ATTR_DEF_NOT_ZERO	= cpu_to_le32(0x08), /* Attribute value
					must contain at least one non-zero
					byte. */
	ATTR_DEF_INDEXED_UNIQUE	= cpu_to_le32(0x10), /* Attribute must be
					indexed and the attribute value must be
					unique क्रम the attribute type in all of
					the mft records of an inode. */
	ATTR_DEF_NAMED_UNIQUE	= cpu_to_le32(0x20), /* Attribute must be
					named and the name must be unique क्रम
					the attribute type in all of the mft
					records of an inode. */
	ATTR_DEF_RESIDENT	= cpu_to_le32(0x40), /* Attribute must be
					resident. */
	ATTR_DEF_ALWAYS_LOG	= cpu_to_le32(0x80), /* Always log
					modअगरications to this attribute,
					regardless of whether it is resident or
					non-resident.  Without this, only log
					modअगरications अगर the attribute is
					resident. */
पूर्ण;

प्रकार le32 ATTR_DEF_FLAGS;

/*
 * The data attribute of खाता_AttrDef contains a sequence of attribute
 * definitions क्रम the NTFS volume. With this, it is supposed to be safe क्रम an
 * older NTFS driver to mount a volume containing a newer NTFS version without
 * damaging it (that's the theory. In practice it's: not damaging it too much).
 * Entries are sorted by attribute type. The flags describe whether the
 * attribute can be resident/non-resident and possibly other things, but the
 * actual bits are unknown.
 */
प्रकार काष्ठा अणु
/*hex ofs*/
/*  0*/	ntfsअक्षर name[0x40];		/* Unicode name of the attribute. Zero
					   terminated. */
/* 80*/	ATTR_TYPE type;			/* Type of the attribute. */
/* 84*/	le32 display_rule;		/* Default display rule.
					   FIXME: What करोes it mean? (AIA) */
/* 88*/ COLLATION_RULE collation_rule;	/* Default collation rule. */
/* 8c*/	ATTR_DEF_FLAGS flags;		/* Flags describing the attribute. */
/* 90*/	sle64 min_size;			/* Optional minimum attribute size. */
/* 98*/	sle64 max_size;			/* Maximum size of attribute. */
/* माप() = 0xa0 or 160 bytes */
पूर्ण __attribute__ ((__packed__)) ATTR_DEF;

/*
 * Attribute flags (16-bit).
 */
क्रमागत अणु
	ATTR_IS_COMPRESSED    = cpu_to_le16(0x0001),
	ATTR_COMPRESSION_MASK = cpu_to_le16(0x00ff), /* Compression method
							      mask.  Also, first
							      illegal value. */
	ATTR_IS_ENCRYPTED     = cpu_to_le16(0x4000),
	ATTR_IS_SPARSE	      = cpu_to_le16(0x8000),
पूर्ण __attribute__ ((__packed__));

प्रकार le16 ATTR_FLAGS;

/*
 * Attribute compression.
 *
 * Only the data attribute is ever compressed in the current ntfs driver in
 * Winकरोws. Further, compression is only applied when the data attribute is
 * non-resident. Finally, to use compression, the maximum allowed cluster size
 * on a volume is 4kib.
 *
 * The compression method is based on independently compressing blocks of X
 * clusters, where X is determined from the compression_unit value found in the
 * non-resident attribute record header (more precisely: X = 2^compression_unit
 * clusters). On Winकरोws NT/2k, X always is 16 clusters (compression_unit = 4).
 *
 * There are three dअगरferent हालs of how a compression block of X clusters
 * can be stored:
 *
 *   1) The data in the block is all zero (a sparse block):
 *	  This is stored as a sparse block in the runlist, i.e. the runlist
 *	  entry has length = X and lcn = -1. The mapping pairs array actually
 *	  uses a delta_lcn value length of 0, i.e. delta_lcn is not present at
 *	  all, which is then पूर्णांकerpreted by the driver as lcn = -1.
 *	  NOTE: Even uncompressed files can be sparse on NTFS 3.0 volumes, then
 *	  the same principles apply as above, except that the length is not
 *	  restricted to being any particular value.
 *
 *   2) The data in the block is not compressed:
 *	  This happens when compression करोesn't reduce the size of the block
 *	  in clusters. I.e. अगर compression has a small effect so that the
 *	  compressed data still occupies X clusters, then the uncompressed data
 *	  is stored in the block.
 *	  This हाल is recognised by the fact that the runlist entry has
 *	  length = X and lcn >= 0. The mapping pairs array stores this as
 *	  normal with a run length of X and some specअगरic delta_lcn, i.e.
 *	  delta_lcn has to be present.
 *
 *   3) The data in the block is compressed:
 *	  The common हाल. This हाल is recognised by the fact that the run
 *	  list entry has length L < X and lcn >= 0. The mapping pairs array
 *	  stores this as normal with a run length of X and some specअगरic
 *	  delta_lcn, i.e. delta_lcn has to be present. This runlist entry is
 *	  immediately followed by a sparse entry with length = X - L and
 *	  lcn = -1. The latter entry is to make up the vcn counting to the
 *	  full compression block size X.
 *
 * In fact, lअगरe is more complicated because adjacent entries of the same type
 * can be coalesced. This means that one has to keep track of the number of
 * clusters handled and work on a basis of X clusters at a समय being one
 * block. An example: अगर length L > X this means that this particular runlist
 * entry contains a block of length X and part of one or more blocks of length
 * L - X. Another example: अगर length L < X, this करोes not necessarily mean that
 * the block is compressed as it might be that the lcn changes inside the block
 * and hence the following runlist entry describes the continuation of the
 * potentially compressed block. The block would be compressed अगर the
 * following runlist entry describes at least X - L sparse clusters, thus
 * making up the compression block length as described in poपूर्णांक 3 above. (Of
 * course, there can be several runlist entries with small lengths so that the
 * sparse entry करोes not follow the first data containing entry with
 * length < X.)
 *
 * NOTE: At the end of the compressed attribute value, there most likely is not
 * just the right amount of data to make up a compression block, thus this data
 * is not even attempted to be compressed. It is just stored as is, unless
 * the number of clusters it occupies is reduced when compressed in which हाल
 * it is stored as a compressed compression block, complete with sparse
 * clusters at the end.
 */

/*
 * Flags of resident attributes (8-bit).
 */
क्रमागत अणु
	RESIDENT_ATTR_IS_INDEXED = 0x01, /* Attribute is referenced in an index
					    (has implications क्रम deleting and
					    modअगरying the attribute). */
पूर्ण __attribute__ ((__packed__));

प्रकार u8 RESIDENT_ATTR_FLAGS;

/*
 * Attribute record header. Always aligned to 8-byte boundary.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	ATTR_TYPE type;		/* The (32-bit) type of the attribute. */
/*  4*/	le32 length;		/* Byte size of the resident part of the
				   attribute (aligned to 8-byte boundary).
				   Used to get to the next attribute. */
/*  8*/	u8 non_resident;	/* If 0, attribute is resident.
				   If 1, attribute is non-resident. */
/*  9*/	u8 name_length;		/* Unicode अक्षरacter size of name of attribute.
				   0 अगर unnamed. */
/* 10*/	le16 name_offset;	/* If name_length != 0, the byte offset to the
				   beginning of the name from the attribute
				   record. Note that the name is stored as a
				   Unicode string. When creating, place offset
				   just at the end of the record header. Then,
				   follow with attribute value or mapping pairs
				   array, resident and non-resident attributes
				   respectively, aligning to an 8-byte
				   boundary. */
/* 12*/	ATTR_FLAGS flags;	/* Flags describing the attribute. */
/* 14*/	le16 instance;		/* The instance of this attribute record. This
				   number is unique within this mft record (see
				   MFT_RECORD/next_attribute_instance notes in
				   mft.h क्रम more details). */
/* 16*/	जोड़ अणु
		/* Resident attributes. */
		काष्ठा अणु
/* 16 */		le32 value_length;/* Byte size of attribute value. */
/* 20 */		le16 value_offset;/* Byte offset of the attribute
					     value from the start of the
					     attribute record. When creating,
					     align to 8-byte boundary अगर we
					     have a name present as this might
					     not have a length of a multiple
					     of 8-bytes. */
/* 22 */		RESIDENT_ATTR_FLAGS flags; /* See above. */
/* 23 */		s8 reserved;	  /* Reserved/alignment to 8-byte
					     boundary. */
		पूर्ण __attribute__ ((__packed__)) resident;
		/* Non-resident attributes. */
		काष्ठा अणु
/* 16*/			leVCN lowest_vcn;/* Lowest valid भव cluster number
				क्रम this portion of the attribute value or
				0 अगर this is the only extent (usually the
				हाल). - Only when an attribute list is used
				करोes lowest_vcn != 0 ever occur. */
/* 24*/			leVCN highest_vcn;/* Highest valid vcn of this extent of
				the attribute value. - Usually there is only one
				portion, so this usually equals the attribute
				value size in clusters minus 1. Can be -1 क्रम
				zero length files. Can be 0 क्रम "single extent"
				attributes. */
/* 32*/			le16 mapping_pairs_offset; /* Byte offset from the
				beginning of the काष्ठाure to the mapping pairs
				array which contains the mappings between the
				vcns and the logical cluster numbers (lcns).
				When creating, place this at the end of this
				record header aligned to 8-byte boundary. */
/* 34*/			u8 compression_unit; /* The compression unit expressed
				as the log to the base 2 of the number of
				clusters in a compression unit.  0 means not
				compressed.  (This effectively limits the
				compression unit size to be a घातer of two
				clusters.)  WinNT4 only uses a value of 4.
				Sparse files have this set to 0 on XPSP2. */
/* 35*/			u8 reserved[5];		/* Align to 8-byte boundary. */
/* The sizes below are only used when lowest_vcn is zero, as otherwise it would
   be dअगरficult to keep them up-to-date.*/
/* 40*/			sle64 allocated_size;	/* Byte size of disk space
				allocated to hold the attribute value. Always
				is a multiple of the cluster size. When a file
				is compressed, this field is a multiple of the
				compression block size (2^compression_unit) and
				it represents the logically allocated space
				rather than the actual on disk usage. For this
				use the compressed_size (see below). */
/* 48*/			sle64 data_size;	/* Byte size of the attribute
				value. Can be larger than allocated_size अगर
				attribute value is compressed or sparse. */
/* 56*/			sle64 initialized_size;	/* Byte size of initialized
				portion of the attribute value. Usually equals
				data_size. */
/* माप(uncompressed attr) = 64*/
/* 64*/			sle64 compressed_size;	/* Byte size of the attribute
				value after compression.  Only present when
				compressed or sparse.  Always is a multiple of
				the cluster size.  Represents the actual amount
				of disk space being used on the disk. */
/* माप(compressed attr) = 72*/
		पूर्ण __attribute__ ((__packed__)) non_resident;
	पूर्ण __attribute__ ((__packed__)) data;
पूर्ण __attribute__ ((__packed__)) ATTR_RECORD;

प्रकार ATTR_RECORD ATTR_REC;

/*
 * File attribute flags (32-bit) appearing in the file_attributes fields of the
 * STANDARD_INFORMATION attribute of MFT_RECORDs and the खाताNAME_ATTR
 * attributes of MFT_RECORDs and directory index entries.
 *
 * All of the below flags appear in the directory index entries but only some
 * appear in the STANDARD_INFORMATION attribute whilst only some others appear
 * in the खाताNAME_ATTR attribute of MFT_RECORDs.  Unless otherwise stated the
 * flags appear in all of the above.
 */
क्रमागत अणु
	खाता_ATTR_READONLY		= cpu_to_le32(0x00000001),
	खाता_ATTR_HIDDEN		= cpu_to_le32(0x00000002),
	खाता_ATTR_SYSTEM		= cpu_to_le32(0x00000004),
	/* Old DOS volid. Unused in NT.	= cpu_to_le32(0x00000008), */

	खाता_ATTR_सूचीECTORY		= cpu_to_le32(0x00000010),
	/* Note, खाता_ATTR_सूचीECTORY is not considered valid in NT.  It is
	   reserved क्रम the DOS SUBसूचीECTORY flag. */
	खाता_ATTR_ARCHIVE		= cpu_to_le32(0x00000020),
	खाता_ATTR_DEVICE		= cpu_to_le32(0x00000040),
	खाता_ATTR_NORMAL		= cpu_to_le32(0x00000080),

	खाता_ATTR_TEMPORARY		= cpu_to_le32(0x00000100),
	खाता_ATTR_SPARSE_खाता		= cpu_to_le32(0x00000200),
	खाता_ATTR_REPARSE_POINT		= cpu_to_le32(0x00000400),
	खाता_ATTR_COMPRESSED		= cpu_to_le32(0x00000800),

	खाता_ATTR_OFFLINE		= cpu_to_le32(0x00001000),
	खाता_ATTR_NOT_CONTENT_INDEXED	= cpu_to_le32(0x00002000),
	खाता_ATTR_ENCRYPTED		= cpu_to_le32(0x00004000),

	खाता_ATTR_VALID_FLAGS		= cpu_to_le32(0x00007fb7),
	/* Note, खाता_ATTR_VALID_FLAGS masks out the old DOS VolId and the
	   खाता_ATTR_DEVICE and preserves everything अन्यथा.  This mask is used
	   to obtain all flags that are valid क्रम पढ़ोing. */
	खाता_ATTR_VALID_SET_FLAGS	= cpu_to_le32(0x000031a7),
	/* Note, खाता_ATTR_VALID_SET_FLAGS masks out the old DOS VolId, the
	   F_A_DEVICE, F_A_सूचीECTORY, F_A_SPARSE_खाता, F_A_REPARSE_POINT,
	   F_A_COMPRESSED, and F_A_ENCRYPTED and preserves the rest.  This mask
	   is used to obtain all flags that are valid क्रम setting. */
	/*
	 * The flag खाता_ATTR_DUP_खाताNAME_INDEX_PRESENT is present in all
	 * खाताNAME_ATTR attributes but not in the STANDARD_INFORMATION
	 * attribute of an mft record.
	 */
	खाता_ATTR_DUP_खाता_NAME_INDEX_PRESENT	= cpu_to_le32(0x10000000),
	/* Note, this is a copy of the corresponding bit from the mft record,
	   telling us whether this is a directory or not, i.e. whether it has
	   an index root attribute or not. */
	खाता_ATTR_DUP_VIEW_INDEX_PRESENT	= cpu_to_le32(0x20000000),
	/* Note, this is a copy of the corresponding bit from the mft record,
	   telling us whether this file has a view index present (eg. object id
	   index, quota index, one of the security indexes or the encrypting
	   fileप्रणाली related indexes). */
पूर्ण;

प्रकार le32 खाता_ATTR_FLAGS;

/*
 * NOTE on बार in NTFS: All बार are in MS standard समय क्रमmat, i.e. they
 * are the number of 100-nanosecond पूर्णांकervals since 1st January 1601, 00:00:00
 * universal coordinated समय (UTC). (In Linux समय starts 1st January 1970,
 * 00:00:00 UTC and is stored as the number of 1-second पूर्णांकervals since then.)
 */

/*
 * Attribute: Standard inक्रमmation (0x10).
 *
 * NOTE: Always resident.
 * NOTE: Present in all base file records on a volume.
 * NOTE: There is conflicting inक्रमmation about the meaning of each of the समय
 *	 fields but the meaning as defined below has been verअगरied to be
 *	 correct by practical experimentation on Winकरोws NT4 SP6a and is hence
 *	 assumed to be the one and only correct पूर्णांकerpretation.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	sle64 creation_समय;		/* Time file was created. Updated when
					   a filename is changed(?). */
/*  8*/	sle64 last_data_change_समय;	/* Time the data attribute was last
					   modअगरied. */
/* 16*/	sle64 last_mft_change_समय;	/* Time this mft record was last
					   modअगरied. */
/* 24*/	sle64 last_access_समय;		/* Approximate समय when the file was
					   last accessed (obviously this is not
					   updated on पढ़ो-only volumes). In
					   Winकरोws this is only updated when
					   accessed अगर some समय delta has
					   passed since the last update. Also,
					   last access समय updates can be
					   disabled altogether क्रम speed. */
/* 32*/	खाता_ATTR_FLAGS file_attributes; /* Flags describing the file. */
/* 36*/	जोड़ अणु
	/* NTFS 1.2 */
		काष्ठा अणु
		/* 36*/	u8 reserved12[12];	/* Reserved/alignment to 8-byte
						   boundary. */
		पूर्ण __attribute__ ((__packed__)) v1;
	/* माप() = 48 bytes */
	/* NTFS 3.x */
		काष्ठा अणु
/*
 * If a volume has been upgraded from a previous NTFS version, then these
 * fields are present only अगर the file has been accessed since the upgrade.
 * Recognize the dअगरference by comparing the length of the resident attribute
 * value. If it is 48, then the following fields are missing. If it is 72 then
 * the fields are present. Maybe just check like this:
 *	अगर (resident.ValueLength < माप(STANDARD_INFORMATION)) अणु
 *		Assume NTFS 1.2- क्रमmat.
 *		If (volume version is 3.x)
 *			Upgrade attribute to NTFS 3.x क्रमmat.
 *		अन्यथा
 *			Use NTFS 1.2- क्रमmat क्रम access.
 *	पूर्ण अन्यथा
 *		Use NTFS 3.x क्रमmat क्रम access.
 * Only problem is that it might be legal to set the length of the value to
 * arbitrarily large values thus spoiling this check. - But chkdsk probably
 * views that as a corruption, assuming that it behaves like this क्रम all
 * attributes.
 */
		/* 36*/	le32 maximum_versions;	/* Maximum allowed versions क्रम
				file. Zero अगर version numbering is disabled. */
		/* 40*/	le32 version_number;	/* This file's version (अगर any).
				Set to zero अगर maximum_versions is zero. */
		/* 44*/	le32 class_id;		/* Class id from bidirectional
				class id index (?). */
		/* 48*/	le32 owner_id;		/* Owner_id of the user owning
				the file. Translate via $Q index in खाता_Extend
				/$Quota to the quota control entry क्रम the user
				owning the file. Zero अगर quotas are disabled. */
		/* 52*/	le32 security_id;	/* Security_id क्रम the file.
				Translate via $SII index and $SDS data stream
				in खाता_Secure to the security descriptor. */
		/* 56*/	le64 quota_अक्षरged;	/* Byte size of the अक्षरge to
				the quota क्रम all streams of the file. Note: Is
				zero अगर quotas are disabled. */
		/* 64*/	leUSN usn;		/* Last update sequence number
				of the file.  This is a direct index पूर्णांकo the
				transaction log file ($UsnJrnl).  It is zero अगर
				the usn journal is disabled or this file has
				not been subject to logging yet.  See usnjrnl.h
				क्रम details. */
		पूर्ण __attribute__ ((__packed__)) v3;
	/* माप() = 72 bytes (NTFS 3.x) */
	पूर्ण __attribute__ ((__packed__)) ver;
पूर्ण __attribute__ ((__packed__)) STANDARD_INFORMATION;

/*
 * Attribute: Attribute list (0x20).
 *
 * - Can be either resident or non-resident.
 * - Value consists of a sequence of variable length, 8-byte aligned,
 * ATTR_LIST_ENTRY records.
 * - The list is not terminated by anything at all! The only way to know when
 * the end is reached is to keep track of the current offset and compare it to
 * the attribute value size.
 * - The attribute list attribute contains one entry क्रम each attribute of
 * the file in which the list is located, except क्रम the list attribute
 * itself. The list is sorted: first by attribute type, second by attribute
 * name (अगर present), third by instance number. The extents of one
 * non-resident attribute (अगर present) immediately follow after the initial
 * extent. They are ordered by lowest_vcn and have their instace set to zero.
 * It is not allowed to have two attributes with all sorting keys equal.
 * - Further restrictions:
 *	- If not resident, the vcn to lcn mapping array has to fit inside the
 *	  base mft record.
 *	- The attribute list attribute value has a maximum size of 256kb. This
 *	  is imposed by the Winकरोws cache manager.
 * - Attribute lists are only used when the attributes of mft record करो not
 * fit inside the mft record despite all attributes (that can be made
 * non-resident) having been made non-resident. This can happen e.g. when:
 *	- File has a large number of hard links (lots of file name
 *	  attributes present).
 *	- The mapping pairs array of some non-resident attribute becomes so
 *	  large due to fragmentation that it overflows the mft record.
 *	- The security descriptor is very complex (not applicable to
 *	  NTFS 3.0 volumes).
 *	- There are many named streams.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	ATTR_TYPE type;		/* Type of referenced attribute. */
/*  4*/	le16 length;		/* Byte size of this entry (8-byte aligned). */
/*  6*/	u8 name_length;		/* Size in Unicode अक्षरs of the name of the
				   attribute or 0 अगर unnamed. */
/*  7*/	u8 name_offset;		/* Byte offset to beginning of attribute name
				   (always set this to where the name would
				   start even अगर unnamed). */
/*  8*/	leVCN lowest_vcn;	/* Lowest भव cluster number of this portion
				   of the attribute value. This is usually 0. It
				   is non-zero क्रम the हाल where one attribute
				   करोes not fit पूर्णांकo one mft record and thus
				   several mft records are allocated to hold
				   this attribute. In the latter हाल, each mft
				   record holds one extent of the attribute and
				   there is one attribute list entry क्रम each
				   extent. NOTE: This is DEFINITELY a चिन्हित
				   value! The winकरोws driver uses cmp, followed
				   by jg when comparing this, thus it treats it
				   as चिन्हित. */
/* 16*/	leMFT_REF mft_reference;/* The reference of the mft record holding
				   the ATTR_RECORD क्रम this portion of the
				   attribute value. */
/* 24*/	le16 instance;		/* If lowest_vcn = 0, the instance of the
				   attribute being referenced; otherwise 0. */
/* 26*/	ntfsअक्षर name[0];	/* Use when creating only. When पढ़ोing use
				   name_offset to determine the location of the
				   name. */
/* माप() = 26 + (attribute_name_length * 2) bytes */
पूर्ण __attribute__ ((__packed__)) ATTR_LIST_ENTRY;

/*
 * The maximum allowed length क्रम a file name.
 */
#घोषणा MAXIMUM_खाता_NAME_LENGTH	255

/*
 * Possible namespaces क्रम filenames in ntfs (8-bit).
 */
क्रमागत अणु
	खाता_NAME_POSIX		= 0x00,
	/* This is the largest namespace. It is हाल sensitive and allows all
	   Unicode अक्षरacters except क्रम: '\0' and '/'.  Beware that in
	   WinNT/2k/2003 by शेष files which eg have the same name except
	   क्रम their हाल will not be distinguished by the standard utilities
	   and thus a "del filename" will delete both "filename" and "fileName"
	   without warning.  However अगर क्रम example Services For Unix (SFU) are
	   installed and the हाल sensitive option was enabled at installation
	   समय, then you can create/access/delete such files.
	   Note that even SFU places restrictions on the filenames beyond the
	   '\0' and '/' and in particular the following set of अक्षरacters is
	   not allowed: '"', '/', '<', '>', '\'.  All other अक्षरacters,
	   including the ones no allowed in WIN32 namespace are allowed.
	   Tested with SFU 3.5 (this is now मुक्त) running on Winकरोws XP. */
	खाता_NAME_WIN32		= 0x01,
	/* The standard WinNT/2k NTFS दीर्घ filenames. Case insensitive.  All
	   Unicode अक्षरs except: '\0', '"', '*', '/', ':', '<', '>', '?', '\',
	   and '|'.  Further, names cannot end with a '.' or a space. */
	खाता_NAME_DOS		= 0x02,
	/* The standard DOS filenames (8.3 क्रमmat). Upperहाल only.  All 8-bit
	   अक्षरacters greater space, except: '"', '*', '+', ',', '/', ':', ';',
	   '<', '=', '>', '?', and '\'. */
	खाता_NAME_WIN32_AND_DOS	= 0x03,
	/* 3 means that both the Win32 and the DOS filenames are identical and
	   hence have been saved in this single filename record. */
पूर्ण __attribute__ ((__packed__));

प्रकार u8 खाता_NAME_TYPE_FLAGS;

/*
 * Attribute: Filename (0x30).
 *
 * NOTE: Always resident.
 * NOTE: All fields, except the parent_directory, are only updated when the
 *	 filename is changed. Until then, they just become out of sync with
 *	 reality and the more up to date values are present in the standard
 *	 inक्रमmation attribute.
 * NOTE: There is conflicting inक्रमmation about the meaning of each of the समय
 *	 fields but the meaning as defined below has been verअगरied to be
 *	 correct by practical experimentation on Winकरोws NT4 SP6a and is hence
 *	 assumed to be the one and only correct पूर्णांकerpretation.
 */
प्रकार काष्ठा अणु
/*hex ofs*/
/*  0*/	leMFT_REF parent_directory;	/* Directory this filename is
					   referenced from. */
/*  8*/	sle64 creation_समय;		/* Time file was created. */
/* 10*/	sle64 last_data_change_समय;	/* Time the data attribute was last
					   modअगरied. */
/* 18*/	sle64 last_mft_change_समय;	/* Time this mft record was last
					   modअगरied. */
/* 20*/	sle64 last_access_समय;		/* Time this mft record was last
					   accessed. */
/* 28*/	sle64 allocated_size;		/* Byte size of on-disk allocated space
					   क्रम the unnamed data attribute.  So
					   क्रम normal $DATA, this is the
					   allocated_size from the unnamed
					   $DATA attribute and क्रम compressed
					   and/or sparse $DATA, this is the
					   compressed_size from the unnamed
					   $DATA attribute.  For a directory or
					   other inode without an unnamed $DATA
					   attribute, this is always 0.  NOTE:
					   This is a multiple of the cluster
					   size. */
/* 30*/	sle64 data_size;		/* Byte size of actual data in unnamed
					   data attribute.  For a directory or
					   other inode without an unnamed $DATA
					   attribute, this is always 0. */
/* 38*/	खाता_ATTR_FLAGS file_attributes;	/* Flags describing the file. */
/* 3c*/	जोड़ अणु
	/* 3c*/	काष्ठा अणु
		/* 3c*/	le16 packed_ea_size;	/* Size of the buffer needed to
						   pack the extended attributes
						   (EAs), अगर such are present.*/
		/* 3e*/	le16 reserved;		/* Reserved क्रम alignment. */
		पूर्ण __attribute__ ((__packed__)) ea;
	/* 3c*/	काष्ठा अणु
		/* 3c*/	le32 reparse_poपूर्णांक_tag;	/* Type of reparse poपूर्णांक,
						   present only in reparse
						   poपूर्णांकs and only अगर there are
						   no EAs. */
		पूर्ण __attribute__ ((__packed__)) rp;
	पूर्ण __attribute__ ((__packed__)) type;
/* 40*/	u8 file_name_length;			/* Length of file name in
						   (Unicode) अक्षरacters. */
/* 41*/	खाता_NAME_TYPE_FLAGS file_name_type;	/* Namespace of the file name.*/
/* 42*/	ntfsअक्षर file_name[0];			/* File name in Unicode. */
पूर्ण __attribute__ ((__packed__)) खाता_NAME_ATTR;

/*
 * GUID काष्ठाures store globally unique identअगरiers (GUID). A GUID is a
 * 128-bit value consisting of one group of eight hexadecimal digits, followed
 * by three groups of four hexadecimal digits each, followed by one group of
 * twelve hexadecimal digits. GUIDs are Microsoft's implementation of the
 * distributed computing environment (DCE) universally unique identअगरier (UUID).
 * Example of a GUID:
 *	1F010768-5A73-BC91-0010A52216A7
 */
प्रकार काष्ठा अणु
	le32 data1;	/* The first eight hexadecimal digits of the GUID. */
	le16 data2;	/* The first group of four hexadecimal digits. */
	le16 data3;	/* The second group of four hexadecimal digits. */
	u8 data4[8];	/* The first two bytes are the third group of four
			   hexadecimal digits. The reमुख्यing six bytes are the
			   final 12 hexadecimal digits. */
पूर्ण __attribute__ ((__packed__)) GUID;

/*
 * खाता_Extend/$ObjId contains an index named $O. This index contains all
 * object_ids present on the volume as the index keys and the corresponding
 * mft_record numbers as the index entry data parts. The data part (defined
 * below) also contains three other object_ids:
 *	birth_volume_id - object_id of खाता_Volume on which the file was first
 *			  created. Optional (i.e. can be zero).
 *	birth_object_id - object_id of file when it was first created. Usually
 *			  equals the object_id. Optional (i.e. can be zero).
 *	करोमुख्य_id	- Reserved (always zero).
 */
प्रकार काष्ठा अणु
	leMFT_REF mft_reference;/* Mft record containing the object_id in
				   the index entry key. */
	जोड़ अणु
		काष्ठा अणु
			GUID birth_volume_id;
			GUID birth_object_id;
			GUID करोमुख्य_id;
		पूर्ण __attribute__ ((__packed__)) origin;
		u8 extended_info[48];
	पूर्ण __attribute__ ((__packed__)) opt;
पूर्ण __attribute__ ((__packed__)) OBJ_ID_INDEX_DATA;

/*
 * Attribute: Object id (NTFS 3.0+) (0x40).
 *
 * NOTE: Always resident.
 */
प्रकार काष्ठा अणु
	GUID object_id;				/* Unique id asचिन्हित to the
						   file.*/
	/* The following fields are optional. The attribute value size is 16
	   bytes, i.e. माप(GUID), अगर these are not present at all. Note,
	   the entries can be present but one or more (or all) can be zero
	   meaning that that particular value(s) is(are) not defined. */
	जोड़ अणु
		काष्ठा अणु
			GUID birth_volume_id;	/* Unique id of volume on which
						   the file was first created.*/
			GUID birth_object_id;	/* Unique id of file when it was
						   first created. */
			GUID करोमुख्य_id;		/* Reserved, zero. */
		पूर्ण __attribute__ ((__packed__)) origin;
		u8 extended_info[48];
	पूर्ण __attribute__ ((__packed__)) opt;
पूर्ण __attribute__ ((__packed__)) OBJECT_ID_ATTR;

/*
 * The pre-defined IDENTIFIER_AUTHORITIES used as SID_IDENTIFIER_AUTHORITY in
 * the SID काष्ठाure (see below).
 */
//प्रकार क्रमागत अणु					/* SID string prefix. */
//	SECURITY_शून्य_SID_AUTHORITY	= अणु0, 0, 0, 0, 0, 0पूर्ण,	/* S-1-0 */
//	SECURITY_WORLD_SID_AUTHORITY	= अणु0, 0, 0, 0, 0, 1पूर्ण,	/* S-1-1 */
//	SECURITY_LOCAL_SID_AUTHORITY	= अणु0, 0, 0, 0, 0, 2पूर्ण,	/* S-1-2 */
//	SECURITY_CREATOR_SID_AUTHORITY	= अणु0, 0, 0, 0, 0, 3पूर्ण,	/* S-1-3 */
//	SECURITY_NON_UNIQUE_AUTHORITY	= अणु0, 0, 0, 0, 0, 4पूर्ण,	/* S-1-4 */
//	SECURITY_NT_SID_AUTHORITY	= अणु0, 0, 0, 0, 0, 5पूर्ण,	/* S-1-5 */
//पूर्ण IDENTIFIER_AUTHORITIES;

/*
 * These relative identअगरiers (RIDs) are used with the above identअगरier
 * authorities to make up universal well-known SIDs.
 *
 * Note: The relative identअगरier (RID) refers to the portion of a SID, which
 * identअगरies a user or group in relation to the authority that issued the SID.
 * For example, the universal well-known SID Creator Owner ID (S-1-3-0) is
 * made up of the identअगरier authority SECURITY_CREATOR_SID_AUTHORITY (3) and
 * the relative identअगरier SECURITY_CREATOR_OWNER_RID (0).
 */
प्रकार क्रमागत अणु					/* Identअगरier authority. */
	SECURITY_शून्य_RID		  = 0,	/* S-1-0 */
	SECURITY_WORLD_RID		  = 0,	/* S-1-1 */
	SECURITY_LOCAL_RID		  = 0,	/* S-1-2 */

	SECURITY_CREATOR_OWNER_RID	  = 0,	/* S-1-3 */
	SECURITY_CREATOR_GROUP_RID	  = 1,	/* S-1-3 */

	SECURITY_CREATOR_OWNER_SERVER_RID = 2,	/* S-1-3 */
	SECURITY_CREATOR_GROUP_SERVER_RID = 3,	/* S-1-3 */

	SECURITY_DIALUP_RID		  = 1,
	SECURITY_NETWORK_RID		  = 2,
	SECURITY_BATCH_RID		  = 3,
	SECURITY_INTERACTIVE_RID	  = 4,
	SECURITY_SERVICE_RID		  = 6,
	SECURITY_ANONYMOUS_LOGON_RID	  = 7,
	SECURITY_PROXY_RID		  = 8,
	SECURITY_ENTERPRISE_CONTROLLERS_RID=9,
	SECURITY_SERVER_LOGON_RID	  = 9,
	SECURITY_PRINCIPAL_SELF_RID	  = 0xa,
	SECURITY_AUTHENTICATED_USER_RID	  = 0xb,
	SECURITY_RESTRICTED_CODE_RID	  = 0xc,
	SECURITY_TERMINAL_SERVER_RID	  = 0xd,

	SECURITY_LOGON_IDS_RID		  = 5,
	SECURITY_LOGON_IDS_RID_COUNT	  = 3,

	SECURITY_LOCAL_SYSTEM_RID	  = 0x12,

	SECURITY_NT_NON_UNIQUE		  = 0x15,

	SECURITY_BUILTIN_DOMAIN_RID	  = 0x20,

	/*
	 * Well-known करोमुख्य relative sub-authority values (RIDs).
	 */

	/* Users. */
	DOMAIN_USER_RID_ADMIN		  = 0x1f4,
	DOMAIN_USER_RID_GUEST		  = 0x1f5,
	DOMAIN_USER_RID_KRBTGT		  = 0x1f6,

	/* Groups. */
	DOMAIN_GROUP_RID_ADMINS		  = 0x200,
	DOMAIN_GROUP_RID_USERS		  = 0x201,
	DOMAIN_GROUP_RID_GUESTS		  = 0x202,
	DOMAIN_GROUP_RID_COMPUTERS	  = 0x203,
	DOMAIN_GROUP_RID_CONTROLLERS	  = 0x204,
	DOMAIN_GROUP_RID_CERT_ADMINS	  = 0x205,
	DOMAIN_GROUP_RID_SCHEMA_ADMINS	  = 0x206,
	DOMAIN_GROUP_RID_ENTERPRISE_ADMINS= 0x207,
	DOMAIN_GROUP_RID_POLICY_ADMINS	  = 0x208,

	/* Aliases. */
	DOMAIN_ALIAS_RID_ADMINS		  = 0x220,
	DOMAIN_ALIAS_RID_USERS		  = 0x221,
	DOMAIN_ALIAS_RID_GUESTS		  = 0x222,
	DOMAIN_ALIAS_RID_POWER_USERS	  = 0x223,

	DOMAIN_ALIAS_RID_ACCOUNT_OPS	  = 0x224,
	DOMAIN_ALIAS_RID_SYSTEM_OPS	  = 0x225,
	DOMAIN_ALIAS_RID_PRINT_OPS	  = 0x226,
	DOMAIN_ALIAS_RID_BACKUP_OPS	  = 0x227,

	DOMAIN_ALIAS_RID_REPLICATOR	  = 0x228,
	DOMAIN_ALIAS_RID_RAS_SERVERS	  = 0x229,
	DOMAIN_ALIAS_RID_PREW2KCOMPACCESS = 0x22a,
पूर्ण RELATIVE_IDENTIFIERS;

/*
 * The universal well-known SIDs:
 *
 *	शून्य_SID			S-1-0-0
 *	WORLD_SID			S-1-1-0
 *	LOCAL_SID			S-1-2-0
 *	CREATOR_OWNER_SID		S-1-3-0
 *	CREATOR_GROUP_SID		S-1-3-1
 *	CREATOR_OWNER_SERVER_SID	S-1-3-2
 *	CREATOR_GROUP_SERVER_SID	S-1-3-3
 *
 *	(Non-unique IDs)		S-1-4
 *
 * NT well-known SIDs:
 *
 *	NT_AUTHORITY_SID	S-1-5
 *	DIALUP_SID		S-1-5-1
 *
 *	NETWORD_SID		S-1-5-2
 *	BATCH_SID		S-1-5-3
 *	INTERACTIVE_SID		S-1-5-4
 *	SERVICE_SID		S-1-5-6
 *	ANONYMOUS_LOGON_SID	S-1-5-7		(aka null logon session)
 *	PROXY_SID		S-1-5-8
 *	SERVER_LOGON_SID	S-1-5-9		(aka करोमुख्य controller account)
 *	SELF_SID		S-1-5-10	(self RID)
 *	AUTHENTICATED_USER_SID	S-1-5-11
 *	RESTRICTED_CODE_SID	S-1-5-12	(running restricted code)
 *	TERMINAL_SERVER_SID	S-1-5-13	(running on terminal server)
 *
 *	(Logon IDs)		S-1-5-5-X-Y
 *
 *	(NT non-unique IDs)	S-1-5-0x15-...
 *
 *	(Built-in करोमुख्य)	S-1-5-0x20
 */

/*
 * The SID_IDENTIFIER_AUTHORITY is a 48-bit value used in the SID काष्ठाure.
 *
 * NOTE: This is stored as a big endian number, hence the high_part comes
 * beक्रमe the low_part.
 */
प्रकार जोड़ अणु
	काष्ठा अणु
		u16 high_part;	/* High 16-bits. */
		u32 low_part;	/* Low 32-bits. */
	पूर्ण __attribute__ ((__packed__)) parts;
	u8 value[6];		/* Value as inभागidual bytes. */
पूर्ण __attribute__ ((__packed__)) SID_IDENTIFIER_AUTHORITY;

/*
 * The SID काष्ठाure is a variable-length काष्ठाure used to uniquely identअगरy
 * users or groups. SID stands क्रम security identअगरier.
 *
 * The standard textual representation of the SID is of the क्रमm:
 *	S-R-I-S-S...
 * Where:
 *    - The first "S" is the literal अक्षरacter 'S' identअगरying the following
 *	digits as a SID.
 *    - R is the revision level of the SID expressed as a sequence of digits
 *	either in decimal or hexadecimal (अगर the later, prefixed by "0x").
 *    - I is the 48-bit identअगरier_authority, expressed as digits as R above.
 *    - S... is one or more sub_authority values, expressed as digits as above.
 *
 * Example SID; the करोमुख्य-relative SID of the local Administrators group on
 * Winकरोws NT/2k:
 *	S-1-5-32-544
 * This translates to a SID with:
 *	revision = 1,
 *	sub_authority_count = 2,
 *	identअगरier_authority = अणु0,0,0,0,0,5पूर्ण,	// SECURITY_NT_AUTHORITY
 *	sub_authority[0] = 32,			// SECURITY_BUILTIN_DOMAIN_RID
 *	sub_authority[1] = 544			// DOMAIN_ALIAS_RID_ADMINS
 */
प्रकार काष्ठा अणु
	u8 revision;
	u8 sub_authority_count;
	SID_IDENTIFIER_AUTHORITY identअगरier_authority;
	le32 sub_authority[1];		/* At least one sub_authority. */
पूर्ण __attribute__ ((__packed__)) SID;

/*
 * Current स्थिरants क्रम SIDs.
 */
प्रकार क्रमागत अणु
	SID_REVISION			=  1,	/* Current revision level. */
	SID_MAX_SUB_AUTHORITIES		= 15,	/* Maximum number of those. */
	SID_RECOMMENDED_SUB_AUTHORITIES	=  1,	/* Will change to around 6 in
						   a future revision. */
पूर्ण SID_CONSTANTS;

/*
 * The predefined ACE types (8-bit, see below).
 */
क्रमागत अणु
	ACCESS_MIN_MS_ACE_TYPE		= 0,
	ACCESS_ALLOWED_ACE_TYPE		= 0,
	ACCESS_DENIED_ACE_TYPE		= 1,
	SYSTEM_AUDIT_ACE_TYPE		= 2,
	SYSTEM_ALARM_ACE_TYPE		= 3, /* Not implemented as of Win2k. */
	ACCESS_MAX_MS_V2_ACE_TYPE	= 3,

	ACCESS_ALLOWED_COMPOUND_ACE_TYPE= 4,
	ACCESS_MAX_MS_V3_ACE_TYPE	= 4,

	/* The following are Win2k only. */
	ACCESS_MIN_MS_OBJECT_ACE_TYPE	= 5,
	ACCESS_ALLOWED_OBJECT_ACE_TYPE	= 5,
	ACCESS_DENIED_OBJECT_ACE_TYPE	= 6,
	SYSTEM_AUDIT_OBJECT_ACE_TYPE	= 7,
	SYSTEM_ALARM_OBJECT_ACE_TYPE	= 8,
	ACCESS_MAX_MS_OBJECT_ACE_TYPE	= 8,

	ACCESS_MAX_MS_V4_ACE_TYPE	= 8,

	/* This one is क्रम WinNT/2k. */
	ACCESS_MAX_MS_ACE_TYPE		= 8,
पूर्ण __attribute__ ((__packed__));

प्रकार u8 ACE_TYPES;

/*
 * The ACE flags (8-bit) क्रम audit and inheritance (see below).
 *
 * SUCCESSFUL_ACCESS_ACE_FLAG is only used with प्रणाली audit and alarm ACE
 * types to indicate that a message is generated (in Winकरोws!) क्रम successful
 * accesses.
 *
 * FAILED_ACCESS_ACE_FLAG is only used with प्रणाली audit and alarm ACE types
 * to indicate that a message is generated (in Winकरोws!) क्रम failed accesses.
 */
क्रमागत अणु
	/* The inheritance flags. */
	OBJECT_INHERIT_ACE		= 0x01,
	CONTAINER_INHERIT_ACE		= 0x02,
	NO_PROPAGATE_INHERIT_ACE	= 0x04,
	INHERIT_ONLY_ACE		= 0x08,
	INHERITED_ACE			= 0x10,	/* Win2k only. */
	VALID_INHERIT_FLAGS		= 0x1f,

	/* The audit flags. */
	SUCCESSFUL_ACCESS_ACE_FLAG	= 0x40,
	FAILED_ACCESS_ACE_FLAG		= 0x80,
पूर्ण __attribute__ ((__packed__));

प्रकार u8 ACE_FLAGS;

/*
 * An ACE is an access-control entry in an access-control list (ACL).
 * An ACE defines access to an object क्रम a specअगरic user or group or defines
 * the types of access that generate प्रणाली-administration messages or alarms
 * क्रम a specअगरic user or group. The user or group is identअगरied by a security
 * identअगरier (SID).
 *
 * Each ACE starts with an ACE_HEADER काष्ठाure (aligned on 4-byte boundary),
 * which specअगरies the type and size of the ACE. The क्रमmat of the subsequent
 * data depends on the ACE type.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0*/	ACE_TYPES type;		/* Type of the ACE. */
/*  1*/	ACE_FLAGS flags;	/* Flags describing the ACE. */
/*  2*/	le16 size;		/* Size in bytes of the ACE. */
पूर्ण __attribute__ ((__packed__)) ACE_HEADER;

/*
 * The access mask (32-bit). Defines the access rights.
 *
 * The specअगरic rights (bits 0 to 15).  These depend on the type of the object
 * being secured by the ACE.
 */
क्रमागत अणु
	/* Specअगरic rights क्रम files and directories are as follows: */

	/* Right to पढ़ो data from the file. (खाता) */
	खाता_READ_DATA			= cpu_to_le32(0x00000001),
	/* Right to list contents of a directory. (सूचीECTORY) */
	खाता_LIST_सूचीECTORY		= cpu_to_le32(0x00000001),

	/* Right to ग_लिखो data to the file. (खाता) */
	खाता_WRITE_DATA			= cpu_to_le32(0x00000002),
	/* Right to create a file in the directory. (सूचीECTORY) */
	खाता_ADD_खाता			= cpu_to_le32(0x00000002),

	/* Right to append data to the file. (खाता) */
	खाता_APPEND_DATA		= cpu_to_le32(0x00000004),
	/* Right to create a subdirectory. (सूचीECTORY) */
	खाता_ADD_SUBसूचीECTORY		= cpu_to_le32(0x00000004),

	/* Right to पढ़ो extended attributes. (खाता/सूचीECTORY) */
	खाता_READ_EA			= cpu_to_le32(0x00000008),

	/* Right to ग_लिखो extended attributes. (खाता/सूचीECTORY) */
	खाता_WRITE_EA			= cpu_to_le32(0x00000010),

	/* Right to execute a file. (खाता) */
	खाता_EXECUTE			= cpu_to_le32(0x00000020),
	/* Right to traverse the directory. (सूचीECTORY) */
	खाता_TRAVERSE			= cpu_to_le32(0x00000020),

	/*
	 * Right to delete a directory and all the files it contains (its
	 * children), even अगर the files are पढ़ो-only. (सूचीECTORY)
	 */
	खाता_DELETE_CHILD		= cpu_to_le32(0x00000040),

	/* Right to पढ़ो file attributes. (खाता/सूचीECTORY) */
	खाता_READ_ATTRIBUTES		= cpu_to_le32(0x00000080),

	/* Right to change file attributes. (खाता/सूचीECTORY) */
	खाता_WRITE_ATTRIBUTES		= cpu_to_le32(0x00000100),

	/*
	 * The standard rights (bits 16 to 23).  These are independent of the
	 * type of object being secured.
	 */

	/* Right to delete the object. */
	DELETE				= cpu_to_le32(0x00010000),

	/*
	 * Right to पढ़ो the inक्रमmation in the object's security descriptor,
	 * not including the inक्रमmation in the SACL, i.e. right to पढ़ो the
	 * security descriptor and owner.
	 */
	READ_CONTROL			= cpu_to_le32(0x00020000),

	/* Right to modअगरy the DACL in the object's security descriptor. */
	WRITE_DAC			= cpu_to_le32(0x00040000),

	/* Right to change the owner in the object's security descriptor. */
	WRITE_OWNER			= cpu_to_le32(0x00080000),

	/*
	 * Right to use the object क्रम synchronization.  Enables a process to
	 * रुको until the object is in the संकेतled state.  Some object types
	 * करो not support this access right.
	 */
	SYNCHRONIZE			= cpu_to_le32(0x00100000),

	/*
	 * The following STANDARD_RIGHTS_* are combinations of the above क्रम
	 * convenience and are defined by the Win32 API.
	 */

	/* These are currently defined to READ_CONTROL. */
	STANDARD_RIGHTS_READ		= cpu_to_le32(0x00020000),
	STANDARD_RIGHTS_WRITE		= cpu_to_le32(0x00020000),
	STANDARD_RIGHTS_EXECUTE		= cpu_to_le32(0x00020000),

	/* Combines DELETE, READ_CONTROL, WRITE_DAC, and WRITE_OWNER access. */
	STANDARD_RIGHTS_REQUIRED	= cpu_to_le32(0x000f0000),

	/*
	 * Combines DELETE, READ_CONTROL, WRITE_DAC, WRITE_OWNER, and
	 * SYNCHRONIZE access.
	 */
	STANDARD_RIGHTS_ALL		= cpu_to_le32(0x001f0000),

	/*
	 * The access प्रणाली ACL and maximum allowed access types (bits 24 to
	 * 25, bits 26 to 27 are reserved).
	 */
	ACCESS_SYSTEM_SECURITY		= cpu_to_le32(0x01000000),
	MAXIMUM_ALLOWED			= cpu_to_le32(0x02000000),

	/*
	 * The generic rights (bits 28 to 31).  These map onto the standard and
	 * specअगरic rights.
	 */

	/* Read, ग_लिखो, and execute access. */
	GENERIC_ALL			= cpu_to_le32(0x10000000),

	/* Execute access. */
	GENERIC_EXECUTE			= cpu_to_le32(0x20000000),

	/*
	 * Write access.  For files, this maps onto:
	 *	खाता_APPEND_DATA | खाता_WRITE_ATTRIBUTES | खाता_WRITE_DATA |
	 *	खाता_WRITE_EA | STANDARD_RIGHTS_WRITE | SYNCHRONIZE
	 * For directories, the mapping has the same numerical value.  See
	 * above क्रम the descriptions of the rights granted.
	 */
	GENERIC_WRITE			= cpu_to_le32(0x40000000),

	/*
	 * Read access.  For files, this maps onto:
	 *	खाता_READ_ATTRIBUTES | खाता_READ_DATA | खाता_READ_EA |
	 *	STANDARD_RIGHTS_READ | SYNCHRONIZE
	 * For directories, the mapping has the same numberical value.  See
	 * above क्रम the descriptions of the rights granted.
	 */
	GENERIC_READ			= cpu_to_le32(0x80000000),
पूर्ण;

प्रकार le32 ACCESS_MASK;

/*
 * The generic mapping array. Used to denote the mapping of each generic
 * access right to a specअगरic access mask.
 *
 * FIXME: What exactly is this and what is it क्रम? (AIA)
 */
प्रकार काष्ठा अणु
	ACCESS_MASK generic_पढ़ो;
	ACCESS_MASK generic_ग_लिखो;
	ACCESS_MASK generic_execute;
	ACCESS_MASK generic_all;
पूर्ण __attribute__ ((__packed__)) GENERIC_MAPPING;

/*
 * The predefined ACE type काष्ठाures are as defined below.
 */

/*
 * ACCESS_ALLOWED_ACE, ACCESS_DENIED_ACE, SYSTEM_AUDIT_ACE, SYSTEM_ALARM_ACE
 */
प्रकार काष्ठा अणु
/*  0	ACE_HEADER; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
	ACE_TYPES type;		/* Type of the ACE. */
	ACE_FLAGS flags;	/* Flags describing the ACE. */
	le16 size;		/* Size in bytes of the ACE. */
/*  4*/	ACCESS_MASK mask;	/* Access mask associated with the ACE. */

/*  8*/	SID sid;		/* The SID associated with the ACE. */
पूर्ण __attribute__ ((__packed__)) ACCESS_ALLOWED_ACE, ACCESS_DENIED_ACE,
			       SYSTEM_AUDIT_ACE, SYSTEM_ALARM_ACE;

/*
 * The object ACE flags (32-bit).
 */
क्रमागत अणु
	ACE_OBJECT_TYPE_PRESENT			= cpu_to_le32(1),
	ACE_INHERITED_OBJECT_TYPE_PRESENT	= cpu_to_le32(2),
पूर्ण;

प्रकार le32 OBJECT_ACE_FLAGS;

प्रकार काष्ठा अणु
/*  0	ACE_HEADER; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
	ACE_TYPES type;		/* Type of the ACE. */
	ACE_FLAGS flags;	/* Flags describing the ACE. */
	le16 size;		/* Size in bytes of the ACE. */
/*  4*/	ACCESS_MASK mask;	/* Access mask associated with the ACE. */

/*  8*/	OBJECT_ACE_FLAGS object_flags;	/* Flags describing the object ACE. */
/* 12*/	GUID object_type;
/* 28*/	GUID inherited_object_type;

/* 44*/	SID sid;		/* The SID associated with the ACE. */
पूर्ण __attribute__ ((__packed__)) ACCESS_ALLOWED_OBJECT_ACE,
			       ACCESS_DENIED_OBJECT_ACE,
			       SYSTEM_AUDIT_OBJECT_ACE,
			       SYSTEM_ALARM_OBJECT_ACE;

/*
 * An ACL is an access-control list (ACL).
 * An ACL starts with an ACL header काष्ठाure, which specअगरies the size of
 * the ACL and the number of ACEs it contains. The ACL header is followed by
 * zero or more access control entries (ACEs). The ACL as well as each ACE
 * are aligned on 4-byte boundaries.
 */
प्रकार काष्ठा अणु
	u8 revision;	/* Revision of this ACL. */
	u8 alignment1;
	le16 size;	/* Allocated space in bytes क्रम ACL. Includes this
			   header, the ACEs and the reमुख्यing मुक्त space. */
	le16 ace_count;	/* Number of ACEs in the ACL. */
	le16 alignment2;
/* माप() = 8 bytes */
पूर्ण __attribute__ ((__packed__)) ACL;

/*
 * Current स्थिरants क्रम ACLs.
 */
प्रकार क्रमागत अणु
	/* Current revision. */
	ACL_REVISION		= 2,
	ACL_REVISION_DS		= 4,

	/* History of revisions. */
	ACL_REVISION1		= 1,
	MIN_ACL_REVISION	= 2,
	ACL_REVISION2		= 2,
	ACL_REVISION3		= 3,
	ACL_REVISION4		= 4,
	MAX_ACL_REVISION	= 4,
पूर्ण ACL_CONSTANTS;

/*
 * The security descriptor control flags (16-bit).
 *
 * SE_OWNER_DEFAULTED - This boolean flag, when set, indicates that the SID
 *	poपूर्णांकed to by the Owner field was provided by a शेषing mechanism
 *	rather than explicitly provided by the original provider of the
 *	security descriptor.  This may affect the treaपंचांगent of the SID with
 *	respect to inheritance of an owner.
 *
 * SE_GROUP_DEFAULTED - This boolean flag, when set, indicates that the SID in
 *	the Group field was provided by a शेषing mechanism rather than
 *	explicitly provided by the original provider of the security
 *	descriptor.  This may affect the treaपंचांगent of the SID with respect to
 *	inheritance of a primary group.
 *
 * SE_DACL_PRESENT - This boolean flag, when set, indicates that the security
 *	descriptor contains a discretionary ACL.  If this flag is set and the
 *	Dacl field of the SECURITY_DESCRIPTOR is null, then a null ACL is
 *	explicitly being specअगरied.
 *
 * SE_DACL_DEFAULTED - This boolean flag, when set, indicates that the ACL
 *	poपूर्णांकed to by the Dacl field was provided by a शेषing mechanism
 *	rather than explicitly provided by the original provider of the
 *	security descriptor.  This may affect the treaपंचांगent of the ACL with
 *	respect to inheritance of an ACL.  This flag is ignored अगर the
 *	DaclPresent flag is not set.
 *
 * SE_SACL_PRESENT - This boolean flag, when set,  indicates that the security
 *	descriptor contains a प्रणाली ACL poपूर्णांकed to by the Sacl field.  If this
 *	flag is set and the Sacl field of the SECURITY_DESCRIPTOR is null, then
 *	an empty (but present) ACL is being specअगरied.
 *
 * SE_SACL_DEFAULTED - This boolean flag, when set, indicates that the ACL
 *	poपूर्णांकed to by the Sacl field was provided by a शेषing mechanism
 *	rather than explicitly provided by the original provider of the
 *	security descriptor.  This may affect the treaपंचांगent of the ACL with
 *	respect to inheritance of an ACL.  This flag is ignored अगर the
 *	SaclPresent flag is not set.
 *
 * SE_SELF_RELATIVE - This boolean flag, when set, indicates that the security
 *	descriptor is in self-relative क्रमm.  In this क्रमm, all fields of the
 *	security descriptor are contiguous in memory and all poपूर्णांकer fields are
 *	expressed as offsets from the beginning of the security descriptor.
 */
क्रमागत अणु
	SE_OWNER_DEFAULTED		= cpu_to_le16(0x0001),
	SE_GROUP_DEFAULTED		= cpu_to_le16(0x0002),
	SE_DACL_PRESENT			= cpu_to_le16(0x0004),
	SE_DACL_DEFAULTED		= cpu_to_le16(0x0008),

	SE_SACL_PRESENT			= cpu_to_le16(0x0010),
	SE_SACL_DEFAULTED		= cpu_to_le16(0x0020),

	SE_DACL_AUTO_INHERIT_REQ	= cpu_to_le16(0x0100),
	SE_SACL_AUTO_INHERIT_REQ	= cpu_to_le16(0x0200),
	SE_DACL_AUTO_INHERITED		= cpu_to_le16(0x0400),
	SE_SACL_AUTO_INHERITED		= cpu_to_le16(0x0800),

	SE_DACL_PROTECTED		= cpu_to_le16(0x1000),
	SE_SACL_PROTECTED		= cpu_to_le16(0x2000),
	SE_RM_CONTROL_VALID		= cpu_to_le16(0x4000),
	SE_SELF_RELATIVE		= cpu_to_le16(0x8000)
पूर्ण __attribute__ ((__packed__));

प्रकार le16 SECURITY_DESCRIPTOR_CONTROL;

/*
 * Self-relative security descriptor. Contains the owner and group SIDs as well
 * as the sacl and dacl ACLs inside the security descriptor itself.
 */
प्रकार काष्ठा अणु
	u8 revision;	/* Revision level of the security descriptor. */
	u8 alignment;
	SECURITY_DESCRIPTOR_CONTROL control; /* Flags qualअगरying the type of
			   the descriptor as well as the following fields. */
	le32 owner;	/* Byte offset to a SID representing an object's
			   owner. If this is शून्य, no owner SID is present in
			   the descriptor. */
	le32 group;	/* Byte offset to a SID representing an object's
			   primary group. If this is शून्य, no primary group
			   SID is present in the descriptor. */
	le32 sacl;	/* Byte offset to a प्रणाली ACL. Only valid, अगर
			   SE_SACL_PRESENT is set in the control field. If
			   SE_SACL_PRESENT is set but sacl is शून्य, a शून्य ACL
			   is specअगरied. */
	le32 dacl;	/* Byte offset to a discretionary ACL. Only valid, अगर
			   SE_DACL_PRESENT is set in the control field. If
			   SE_DACL_PRESENT is set but dacl is शून्य, a शून्य ACL
			   (unconditionally granting access) is specअगरied. */
/* माप() = 0x14 bytes */
पूर्ण __attribute__ ((__packed__)) SECURITY_DESCRIPTOR_RELATIVE;

/*
 * Absolute security descriptor. Does not contain the owner and group SIDs, nor
 * the sacl and dacl ACLs inside the security descriptor. Instead, it contains
 * poपूर्णांकers to these काष्ठाures in memory. Obviously, असलolute security
 * descriptors are only useful क्रम in memory representations of security
 * descriptors. On disk, a self-relative security descriptor is used.
 */
प्रकार काष्ठा अणु
	u8 revision;	/* Revision level of the security descriptor. */
	u8 alignment;
	SECURITY_DESCRIPTOR_CONTROL control;	/* Flags qualअगरying the type of
			   the descriptor as well as the following fields. */
	SID *owner;	/* Poपूर्णांकs to a SID representing an object's owner. If
			   this is शून्य, no owner SID is present in the
			   descriptor. */
	SID *group;	/* Poपूर्णांकs to a SID representing an object's primary
			   group. If this is शून्य, no primary group SID is
			   present in the descriptor. */
	ACL *sacl;	/* Poपूर्णांकs to a प्रणाली ACL. Only valid, अगर
			   SE_SACL_PRESENT is set in the control field. If
			   SE_SACL_PRESENT is set but sacl is शून्य, a शून्य ACL
			   is specअगरied. */
	ACL *dacl;	/* Poपूर्णांकs to a discretionary ACL. Only valid, अगर
			   SE_DACL_PRESENT is set in the control field. If
			   SE_DACL_PRESENT is set but dacl is शून्य, a शून्य ACL
			   (unconditionally granting access) is specअगरied. */
पूर्ण __attribute__ ((__packed__)) SECURITY_DESCRIPTOR;

/*
 * Current स्थिरants क्रम security descriptors.
 */
प्रकार क्रमागत अणु
	/* Current revision. */
	SECURITY_DESCRIPTOR_REVISION	= 1,
	SECURITY_DESCRIPTOR_REVISION1	= 1,

	/* The sizes of both the असलolute and relative security descriptors is
	   the same as poपूर्णांकers, at least on ia32 architecture are 32-bit. */
	SECURITY_DESCRIPTOR_MIN_LENGTH	= माप(SECURITY_DESCRIPTOR),
पूर्ण SECURITY_DESCRIPTOR_CONSTANTS;

/*
 * Attribute: Security descriptor (0x50). A standard self-relative security
 * descriptor.
 *
 * NOTE: Can be resident or non-resident.
 * NOTE: Not used in NTFS 3.0+, as security descriptors are stored centrally
 * in खाता_Secure and the correct descriptor is found using the security_id
 * from the standard inक्रमmation attribute.
 */
प्रकार SECURITY_DESCRIPTOR_RELATIVE SECURITY_DESCRIPTOR_ATTR;

/*
 * On NTFS 3.0+, all security descriptors are stored in खाता_Secure. Only one
 * referenced instance of each unique security descriptor is stored.
 *
 * खाता_Secure contains no unnamed data attribute, i.e. it has zero length. It
 * करोes, however, contain two indexes ($SDH and $SII) as well as a named data
 * stream ($SDS).
 *
 * Every unique security descriptor is asचिन्हित a unique security identअगरier
 * (security_id, not to be confused with a SID). The security_id is unique क्रम
 * the NTFS volume and is used as an index पूर्णांकo the $SII index, which maps
 * security_ids to the security descriptor's storage location within the $SDS
 * data attribute. The $SII index is sorted by ascending security_id.
 *
 * A simple hash is computed from each security descriptor. This hash is used
 * as an index पूर्णांकo the $SDH index, which maps security descriptor hashes to
 * the security descriptor's storage location within the $SDS data attribute.
 * The $SDH index is sorted by security descriptor hash and is stored in a B+
 * tree. When searching $SDH (with the पूर्णांकent of determining whether or not a
 * new security descriptor is alपढ़ोy present in the $SDS data stream), अगर a
 * matching hash is found, but the security descriptors करो not match, the
 * search in the $SDH index is जारीd, searching क्रम a next matching hash.
 *
 * When a precise match is found, the security_id coresponding to the security
 * descriptor in the $SDS attribute is पढ़ो from the found $SDH index entry and
 * is stored in the $STANDARD_INFORMATION attribute of the file/directory to
 * which the security descriptor is being applied. The $STANDARD_INFORMATION
 * attribute is present in all base mft records (i.e. in all files and
 * directories).
 *
 * If a match is not found, the security descriptor is asचिन्हित a new unique
 * security_id and is added to the $SDS data attribute. Then, entries
 * referencing the this security descriptor in the $SDS data attribute are
 * added to the $SDH and $SII indexes.
 *
 * Note: Entries are never deleted from खाता_Secure, even अगर nothing
 * references an entry any more.
 */

/*
 * This header precedes each security descriptor in the $SDS data stream.
 * This is also the index entry data part of both the $SII and $SDH indexes.
 */
प्रकार काष्ठा अणु
	le32 hash;	  /* Hash of the security descriptor. */
	le32 security_id; /* The security_id asचिन्हित to the descriptor. */
	le64 offset;	  /* Byte offset of this entry in the $SDS stream. */
	le32 length;	  /* Size in bytes of this entry in $SDS stream. */
पूर्ण __attribute__ ((__packed__)) SECURITY_DESCRIPTOR_HEADER;

/*
 * The $SDS data stream contains the security descriptors, aligned on 16-byte
 * boundaries, sorted by security_id in a B+ tree. Security descriptors cannot
 * cross 256kib boundaries (this restriction is imposed by the Winकरोws cache
 * manager). Each security descriptor is contained in a SDS_ENTRY काष्ठाure.
 * Also, each security descriptor is stored twice in the $SDS stream with a
 * fixed offset of 0x40000 bytes (256kib, the Winकरोws cache manager's max size)
 * between them; i.e. अगर a SDS_ENTRY specअगरies an offset of 0x51d0, then the
 * first copy of the security descriptor will be at offset 0x51d0 in the
 * $SDS data stream and the second copy will be at offset 0x451d0.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0	SECURITY_DESCRIPTOR_HEADER; -- Unfolded here as gcc करोesn't like
				       unnamed काष्ठाs. */
	le32 hash;	  /* Hash of the security descriptor. */
	le32 security_id; /* The security_id asचिन्हित to the descriptor. */
	le64 offset;	  /* Byte offset of this entry in the $SDS stream. */
	le32 length;	  /* Size in bytes of this entry in $SDS stream. */
/* 20*/	SECURITY_DESCRIPTOR_RELATIVE sid; /* The self-relative security
					     descriptor. */
पूर्ण __attribute__ ((__packed__)) SDS_ENTRY;

/*
 * The index entry key used in the $SII index. The collation type is
 * COLLATION_NTOFS_ULONG.
 */
प्रकार काष्ठा अणु
	le32 security_id; /* The security_id asचिन्हित to the descriptor. */
पूर्ण __attribute__ ((__packed__)) SII_INDEX_KEY;

/*
 * The index entry key used in the $SDH index. The keys are sorted first by
 * hash and then by security_id. The collation rule is
 * COLLATION_NTOFS_SECURITY_HASH.
 */
प्रकार काष्ठा अणु
	le32 hash;	  /* Hash of the security descriptor. */
	le32 security_id; /* The security_id asचिन्हित to the descriptor. */
पूर्ण __attribute__ ((__packed__)) SDH_INDEX_KEY;

/*
 * Attribute: Volume name (0x60).
 *
 * NOTE: Always resident.
 * NOTE: Present only in खाता_Volume.
 */
प्रकार काष्ठा अणु
	ntfsअक्षर name[0];	/* The name of the volume in Unicode. */
पूर्ण __attribute__ ((__packed__)) VOLUME_NAME;

/*
 * Possible flags क्रम the volume (16-bit).
 */
क्रमागत अणु
	VOLUME_IS_सूचीTY			= cpu_to_le16(0x0001),
	VOLUME_RESIZE_LOG_खाता		= cpu_to_le16(0x0002),
	VOLUME_UPGRADE_ON_MOUNT		= cpu_to_le16(0x0004),
	VOLUME_MOUNTED_ON_NT4		= cpu_to_le16(0x0008),

	VOLUME_DELETE_USN_UNDERWAY	= cpu_to_le16(0x0010),
	VOLUME_REPAIR_OBJECT_ID		= cpu_to_le16(0x0020),

	VOLUME_CHKDSK_UNDERWAY		= cpu_to_le16(0x4000),
	VOLUME_MODIFIED_BY_CHKDSK	= cpu_to_le16(0x8000),

	VOLUME_FLAGS_MASK		= cpu_to_le16(0xc03f),

	/* To make our lअगरe easier when checking अगर we must mount पढ़ो-only. */
	VOLUME_MUST_MOUNT_RO_MASK	= cpu_to_le16(0xc027),
पूर्ण __attribute__ ((__packed__));

प्रकार le16 VOLUME_FLAGS;

/*
 * Attribute: Volume inक्रमmation (0x70).
 *
 * NOTE: Always resident.
 * NOTE: Present only in खाता_Volume.
 * NOTE: Winकरोws 2000 uses NTFS 3.0 जबतक Winकरोws NT4 service pack 6a uses
 *	 NTFS 1.2. I haven't personally seen other values yet.
 */
प्रकार काष्ठा अणु
	le64 reserved;		/* Not used (yet?). */
	u8 major_ver;		/* Major version of the ntfs क्रमmat. */
	u8 minor_ver;		/* Minor version of the ntfs क्रमmat. */
	VOLUME_FLAGS flags;	/* Bit array of VOLUME_* flags. */
पूर्ण __attribute__ ((__packed__)) VOLUME_INFORMATION;

/*
 * Attribute: Data attribute (0x80).
 *
 * NOTE: Can be resident or non-resident.
 *
 * Data contents of a file (i.e. the unnamed stream) or of a named stream.
 */
प्रकार काष्ठा अणु
	u8 data[0];		/* The file's data contents. */
पूर्ण __attribute__ ((__packed__)) DATA_ATTR;

/*
 * Index header flags (8-bit).
 */
क्रमागत अणु
	/*
	 * When index header is in an index root attribute:
	 */
	SMALL_INDEX = 0, /* The index is small enough to fit inside the index
			    root attribute and there is no index allocation
			    attribute present. */
	LARGE_INDEX = 1, /* The index is too large to fit in the index root
			    attribute and/or an index allocation attribute is
			    present. */
	/*
	 * When index header is in an index block, i.e. is part of index
	 * allocation attribute:
	 */
	LEAF_NODE  = 0, /* This is a leaf node, i.e. there are no more nodes
			   branching off it. */
	INDEX_NODE = 1, /* This node indexes other nodes, i.e. it is not a leaf
			   node. */
	NODE_MASK  = 1, /* Mask क्रम accessing the *_NODE bits. */
पूर्ण __attribute__ ((__packed__));

प्रकार u8 INDEX_HEADER_FLAGS;

/*
 * This is the header क्रम indexes, describing the INDEX_ENTRY records, which
 * follow the INDEX_HEADER. Together the index header and the index entries
 * make up a complete index.
 *
 * IMPORTANT NOTE: The offset, length and size काष्ठाure members are counted
 * relative to the start of the index header काष्ठाure and not relative to the
 * start of the index root or index allocation काष्ठाures themselves.
 */
प्रकार काष्ठा अणु
	le32 entries_offset;		/* Byte offset to first INDEX_ENTRY
					   aligned to 8-byte boundary. */
	le32 index_length;		/* Data size of the index in bytes,
					   i.e. bytes used from allocated
					   size, aligned to 8-byte boundary. */
	le32 allocated_size;		/* Byte size of this index (block),
					   multiple of 8 bytes. */
	/* NOTE: For the index root attribute, the above two numbers are always
	   equal, as the attribute is resident and it is resized as needed. In
	   the हाल of the index allocation attribute the attribute is not
	   resident and hence the allocated_size is a fixed value and must
	   equal the index_block_size specअगरied by the INDEX_ROOT attribute
	   corresponding to the INDEX_ALLOCATION attribute this INDEX_BLOCK
	   beदीर्घs to. */
	INDEX_HEADER_FLAGS flags;	/* Bit field of INDEX_HEADER_FLAGS. */
	u8 reserved[3];			/* Reserved/align to 8-byte boundary. */
पूर्ण __attribute__ ((__packed__)) INDEX_HEADER;

/*
 * Attribute: Index root (0x90).
 *
 * NOTE: Always resident.
 *
 * This is followed by a sequence of index entries (INDEX_ENTRY काष्ठाures)
 * as described by the index header.
 *
 * When a directory is small enough to fit inside the index root then this
 * is the only attribute describing the directory. When the directory is too
 * large to fit in the index root, on the other hand, two additional attributes
 * are present: an index allocation attribute, containing sub-nodes of the B+
 * directory tree (see below), and a biपंचांगap attribute, describing which भव
 * cluster numbers (vcns) in the index allocation attribute are in use by an
 * index block.
 *
 * NOTE: The root directory (खाता_root) contains an entry क्रम itself. Other
 * directories करो not contain entries क्रम themselves, though.
 */
प्रकार काष्ठा अणु
	ATTR_TYPE type;			/* Type of the indexed attribute. Is
					   $खाता_NAME क्रम directories, zero
					   क्रम view indexes. No other values
					   allowed. */
	COLLATION_RULE collation_rule;	/* Collation rule used to sort the
					   index entries. If type is $खाता_NAME,
					   this must be COLLATION_खाता_NAME. */
	le32 index_block_size;		/* Size of each index block in bytes (in
					   the index allocation attribute). */
	u8 clusters_per_index_block;	/* Cluster size of each index block (in
					   the index allocation attribute), when
					   an index block is >= than a cluster,
					   otherwise this will be the log of
					   the size (like how the encoding of
					   the mft record size and the index
					   record size found in the boot sector
					   work). Has to be a घातer of 2. */
	u8 reserved[3];			/* Reserved/align to 8-byte boundary. */
	INDEX_HEADER index;		/* Index header describing the
					   following index entries. */
पूर्ण __attribute__ ((__packed__)) INDEX_ROOT;

/*
 * Attribute: Index allocation (0xa0).
 *
 * NOTE: Always non-resident (करोesn't make sense to be resident anyway!).
 *
 * This is an array of index blocks. Each index block starts with an
 * INDEX_BLOCK काष्ठाure containing an index header, followed by a sequence of
 * index entries (INDEX_ENTRY काष्ठाures), as described by the INDEX_HEADER.
 */
प्रकार काष्ठा अणु
/*  0	NTFS_RECORD; -- Unfolded here as gcc करोesn't like unnamed काष्ठाs. */
	NTFS_RECORD_TYPE magic;	/* Magic is "INDX". */
	le16 usa_ofs;		/* See NTFS_RECORD definition. */
	le16 usa_count;		/* See NTFS_RECORD definition. */

/*  8*/	sle64 lsn;		/* $LogFile sequence number of the last
				   modअगरication of this index block. */
/* 16*/	leVCN index_block_vcn;	/* Virtual cluster number of the index block.
				   If the cluster_size on the volume is <= the
				   index_block_size of the directory,
				   index_block_vcn counts in units of clusters,
				   and in units of sectors otherwise. */
/* 24*/	INDEX_HEADER index;	/* Describes the following index entries. */
/* माप()= 40 (0x28) bytes */
/*
 * When creating the index block, we place the update sequence array at this
 * offset, i.e. beक्रमe we start with the index entries. This also makes sense,
 * otherwise we could run पूर्णांकo problems with the update sequence array
 * containing in itself the last two bytes of a sector which would mean that
 * multi sector transfer protection wouldn't work. As you can't protect data
 * by overwriting it since you then can't get it back...
 * When पढ़ोing use the data from the ntfs record header.
 */
पूर्ण __attribute__ ((__packed__)) INDEX_BLOCK;

प्रकार INDEX_BLOCK INDEX_ALLOCATION;

/*
 * The प्रणाली file खाता_Extend/$Reparse contains an index named $R listing
 * all reparse poपूर्णांकs on the volume. The index entry keys are as defined
 * below. Note, that there is no index data associated with the index entries.
 *
 * The index entries are sorted by the index key file_id. The collation rule is
 * COLLATION_NTOFS_ULONGS. FIXME: Verअगरy whether the reparse_tag is not the
 * primary key / is not a key at all. (AIA)
 */
प्रकार काष्ठा अणु
	le32 reparse_tag;	/* Reparse poपूर्णांक type (inc. flags). */
	leMFT_REF file_id;	/* Mft record of the file containing the
				   reparse poपूर्णांक attribute. */
पूर्ण __attribute__ ((__packed__)) REPARSE_INDEX_KEY;

/*
 * Quota flags (32-bit).
 *
 * The user quota flags.  Names explain meaning.
 */
क्रमागत अणु
	QUOTA_FLAG_DEFAULT_LIMITS	= cpu_to_le32(0x00000001),
	QUOTA_FLAG_LIMIT_REACHED	= cpu_to_le32(0x00000002),
	QUOTA_FLAG_ID_DELETED		= cpu_to_le32(0x00000004),

	QUOTA_FLAG_USER_MASK		= cpu_to_le32(0x00000007),
	/* This is a bit mask क्रम the user quota flags. */

	/*
	 * These flags are only present in the quota शेषs index entry, i.e.
	 * in the entry where owner_id = QUOTA_DEFAULTS_ID.
	 */
	QUOTA_FLAG_TRACKING_ENABLED	= cpu_to_le32(0x00000010),
	QUOTA_FLAG_ENFORCEMENT_ENABLED	= cpu_to_le32(0x00000020),
	QUOTA_FLAG_TRACKING_REQUESTED	= cpu_to_le32(0x00000040),
	QUOTA_FLAG_LOG_THRESHOLD	= cpu_to_le32(0x00000080),

	QUOTA_FLAG_LOG_LIMIT		= cpu_to_le32(0x00000100),
	QUOTA_FLAG_OUT_OF_DATE		= cpu_to_le32(0x00000200),
	QUOTA_FLAG_CORRUPT		= cpu_to_le32(0x00000400),
	QUOTA_FLAG_PENDING_DELETES	= cpu_to_le32(0x00000800),
पूर्ण;

प्रकार le32 QUOTA_FLAGS;

/*
 * The प्रणाली file खाता_Extend/$Quota contains two indexes $O and $Q. Quotas
 * are on a per volume and per user basis.
 *
 * The $Q index contains one entry क्रम each existing user_id on the volume. The
 * index key is the user_id of the user/group owning this quota control entry,
 * i.e. the key is the owner_id. The user_id of the owner of a file, i.e. the
 * owner_id, is found in the standard inक्रमmation attribute. The collation rule
 * क्रम $Q is COLLATION_NTOFS_ULONG.
 *
 * The $O index contains one entry क्रम each user/group who has been asचिन्हित
 * a quota on that volume. The index key holds the SID of the user_id the
 * entry beदीर्घs to, i.e. the owner_id. The collation rule क्रम $O is
 * COLLATION_NTOFS_SID.
 *
 * The $O index entry data is the user_id of the user corresponding to the SID.
 * This user_id is used as an index पूर्णांकo $Q to find the quota control entry
 * associated with the SID.
 *
 * The $Q index entry data is the quota control entry and is defined below.
 */
प्रकार काष्ठा अणु
	le32 version;		/* Currently equals 2. */
	QUOTA_FLAGS flags;	/* Flags describing this quota entry. */
	le64 bytes_used;	/* How many bytes of the quota are in use. */
	sle64 change_समय;	/* Last समय this quota entry was changed. */
	sle64 threshold;	/* Soft quota (-1 अगर not limited). */
	sle64 limit;		/* Hard quota (-1 अगर not limited). */
	sle64 exceeded_समय;	/* How दीर्घ the soft quota has been exceeded. */
	SID sid;		/* The SID of the user/object associated with
				   this quota entry.  Equals zero क्रम the quota
				   शेषs entry (and in fact on a WinXP
				   volume, it is not present at all). */
पूर्ण __attribute__ ((__packed__)) QUOTA_CONTROL_ENTRY;

/*
 * Predefined owner_id values (32-bit).
 */
क्रमागत अणु
	QUOTA_INVALID_ID	= cpu_to_le32(0x00000000),
	QUOTA_DEFAULTS_ID	= cpu_to_le32(0x00000001),
	QUOTA_FIRST_USER_ID	= cpu_to_le32(0x00000100),
पूर्ण;

/*
 * Current स्थिरants क्रम quota control entries.
 */
प्रकार क्रमागत अणु
	/* Current version. */
	QUOTA_VERSION	= 2,
पूर्ण QUOTA_CONTROL_ENTRY_CONSTANTS;

/*
 * Index entry flags (16-bit).
 */
क्रमागत अणु
	INDEX_ENTRY_NODE = cpu_to_le16(1), /* This entry contains a
			sub-node, i.e. a reference to an index block in क्रमm of
			a भव cluster number (see below). */
	INDEX_ENTRY_END  = cpu_to_le16(2), /* This signअगरies the last
			entry in an index block.  The index entry करोes not
			represent a file but it can poपूर्णांक to a sub-node. */

	INDEX_ENTRY_SPACE_FILLER = cpu_to_le16(0xffff), /* gcc: Force
			क्रमागत bit width to 16-bit. */
पूर्ण __attribute__ ((__packed__));

प्रकार le16 INDEX_ENTRY_FLAGS;

/*
 * This the index entry header (see below).
 */
प्रकार काष्ठा अणु
/*  0*/	जोड़ अणु
		काष्ठा अणु /* Only valid when INDEX_ENTRY_END is not set. */
			leMFT_REF indexed_file;	/* The mft reference of the file
						   described by this index
						   entry. Used क्रम directory
						   indexes. */
		पूर्ण __attribute__ ((__packed__)) dir;
		काष्ठा अणु /* Used क्रम views/indexes to find the entry's data. */
			le16 data_offset;	/* Data byte offset from this
						   INDEX_ENTRY. Follows the
						   index key. */
			le16 data_length;	/* Data length in bytes. */
			le32 reservedV;		/* Reserved (zero). */
		पूर्ण __attribute__ ((__packed__)) vi;
	पूर्ण __attribute__ ((__packed__)) data;
/*  8*/	le16 length;		 /* Byte size of this index entry, multiple of
				    8-bytes. */
/* 10*/	le16 key_length;	 /* Byte size of the key value, which is in the
				    index entry. It follows field reserved. Not
				    multiple of 8-bytes. */
/* 12*/	INDEX_ENTRY_FLAGS flags; /* Bit field of INDEX_ENTRY_* flags. */
/* 14*/	le16 reserved;		 /* Reserved/align to 8-byte boundary. */
/* माप() = 16 bytes */
पूर्ण __attribute__ ((__packed__)) INDEX_ENTRY_HEADER;

/*
 * This is an index entry. A sequence of such entries follows each INDEX_HEADER
 * काष्ठाure. Together they make up a complete index. The index follows either
 * an index root attribute or an index allocation attribute.
 *
 * NOTE: Beक्रमe NTFS 3.0 only filename attributes were indexed.
 */
प्रकार काष्ठा अणु
/*Ofs*/
/*  0	INDEX_ENTRY_HEADER; -- Unfolded here as gcc dislikes unnamed काष्ठाs. */
	जोड़ अणु
		काष्ठा अणु /* Only valid when INDEX_ENTRY_END is not set. */
			leMFT_REF indexed_file;	/* The mft reference of the file
						   described by this index
						   entry. Used क्रम directory
						   indexes. */
		पूर्ण __attribute__ ((__packed__)) dir;
		काष्ठा अणु /* Used क्रम views/indexes to find the entry's data. */
			le16 data_offset;	/* Data byte offset from this
						   INDEX_ENTRY. Follows the
						   index key. */
			le16 data_length;	/* Data length in bytes. */
			le32 reservedV;		/* Reserved (zero). */
		पूर्ण __attribute__ ((__packed__)) vi;
	पूर्ण __attribute__ ((__packed__)) data;
	le16 length;		 /* Byte size of this index entry, multiple of
				    8-bytes. */
	le16 key_length;	 /* Byte size of the key value, which is in the
				    index entry. It follows field reserved. Not
				    multiple of 8-bytes. */
	INDEX_ENTRY_FLAGS flags; /* Bit field of INDEX_ENTRY_* flags. */
	le16 reserved;		 /* Reserved/align to 8-byte boundary. */

/* 16*/	जोड़ अणु		/* The key of the indexed attribute. NOTE: Only present
			   अगर INDEX_ENTRY_END bit in flags is not set. NOTE: On
			   NTFS versions beक्रमe 3.0 the only valid key is the
			   खाता_NAME_ATTR. On NTFS 3.0+ the following
			   additional index keys are defined: */
		खाता_NAME_ATTR file_name;/* $I30 index in directories. */
		SII_INDEX_KEY sii;	/* $SII index in $Secure. */
		SDH_INDEX_KEY sdh;	/* $SDH index in $Secure. */
		GUID object_id;		/* $O index in खाता_Extend/$ObjId: The
					   object_id of the mft record found in
					   the data part of the index. */
		REPARSE_INDEX_KEY reparse;	/* $R index in
						   खाता_Extend/$Reparse. */
		SID sid;		/* $O index in खाता_Extend/$Quota:
					   SID of the owner of the user_id. */
		le32 owner_id;		/* $Q index in खाता_Extend/$Quota:
					   user_id of the owner of the quota
					   control entry in the data part of
					   the index. */
	पूर्ण __attribute__ ((__packed__)) key;
	/* The (optional) index data is inserted here when creating. */
	// leVCN vcn;	/* If INDEX_ENTRY_NODE bit in flags is set, the last
	//		   eight bytes of this index entry contain the भव
	//		   cluster number of the index block that holds the
	//		   entries immediately preceding the current entry (the
	//		   vcn references the corresponding cluster in the data
	//		   of the non-resident index allocation attribute). If
	//		   the key_length is zero, then the vcn immediately
	//		   follows the INDEX_ENTRY_HEADER. Regardless of
	//		   key_length, the address of the 8-byte boundary
	//		   aligned vcn of INDEX_ENTRYअणु_HEADERपूर्ण *ie is given by
	//		   (अक्षर*)ie + le16_to_cpu(ie*)->length) - माप(VCN),
	//		   where माप(VCN) can be hardcoded as 8 अगर wanted. */
पूर्ण __attribute__ ((__packed__)) INDEX_ENTRY;

/*
 * Attribute: Biपंचांगap (0xb0).
 *
 * Contains an array of bits (aka a bitfield).
 *
 * When used in conjunction with the index allocation attribute, each bit
 * corresponds to one index block within the index allocation attribute. Thus
 * the number of bits in the biपंचांगap * index block size / cluster size is the
 * number of clusters in the index allocation attribute.
 */
प्रकार काष्ठा अणु
	u8 biपंचांगap[0];			/* Array of bits. */
पूर्ण __attribute__ ((__packed__)) BITMAP_ATTR;

/*
 * The reparse poपूर्णांक tag defines the type of the reparse poपूर्णांक. It also
 * includes several flags, which further describe the reparse poपूर्णांक.
 *
 * The reparse poपूर्णांक tag is an अचिन्हित 32-bit value भागided in three parts:
 *
 * 1. The least signअगरicant 16 bits (i.e. bits 0 to 15) specअगरiy the type of
 *    the reparse poपूर्णांक.
 * 2. The 13 bits after this (i.e. bits 16 to 28) are reserved क्रम future use.
 * 3. The most signअगरicant three bits are flags describing the reparse poपूर्णांक.
 *    They are defined as follows:
 *	bit 29: Name surrogate bit. If set, the filename is an alias क्रम
 *		another object in the प्रणाली.
 *	bit 30: High-latency bit. If set, accessing the first byte of data will
 *		be slow. (E.g. the data is stored on a tape drive.)
 *	bit 31: Microsoft bit. If set, the tag is owned by Microsoft. User
 *		defined tags have to use zero here.
 *
 * These are the predefined reparse poपूर्णांक tags:
 */
क्रमागत अणु
	IO_REPARSE_TAG_IS_ALIAS		= cpu_to_le32(0x20000000),
	IO_REPARSE_TAG_IS_HIGH_LATENCY	= cpu_to_le32(0x40000000),
	IO_REPARSE_TAG_IS_MICROSOFT	= cpu_to_le32(0x80000000),

	IO_REPARSE_TAG_RESERVED_ZERO	= cpu_to_le32(0x00000000),
	IO_REPARSE_TAG_RESERVED_ONE	= cpu_to_le32(0x00000001),
	IO_REPARSE_TAG_RESERVED_RANGE	= cpu_to_le32(0x00000001),

	IO_REPARSE_TAG_NSS		= cpu_to_le32(0x68000005),
	IO_REPARSE_TAG_NSS_RECOVER	= cpu_to_le32(0x68000006),
	IO_REPARSE_TAG_SIS		= cpu_to_le32(0x68000007),
	IO_REPARSE_TAG_DFS		= cpu_to_le32(0x68000008),

	IO_REPARSE_TAG_MOUNT_POINT	= cpu_to_le32(0x88000003),

	IO_REPARSE_TAG_HSM		= cpu_to_le32(0xa8000004),

	IO_REPARSE_TAG_SYMBOLIC_LINK	= cpu_to_le32(0xe8000000),

	IO_REPARSE_TAG_VALID_VALUES	= cpu_to_le32(0xe000ffff),
पूर्ण;

/*
 * Attribute: Reparse poपूर्णांक (0xc0).
 *
 * NOTE: Can be resident or non-resident.
 */
प्रकार काष्ठा अणु
	le32 reparse_tag;		/* Reparse poपूर्णांक type (inc. flags). */
	le16 reparse_data_length;	/* Byte size of reparse data. */
	le16 reserved;			/* Align to 8-byte boundary. */
	u8 reparse_data[0];		/* Meaning depends on reparse_tag. */
पूर्ण __attribute__ ((__packed__)) REPARSE_POINT;

/*
 * Attribute: Extended attribute (EA) inक्रमmation (0xd0).
 *
 * NOTE: Always resident. (Is this true???)
 */
प्रकार काष्ठा अणु
	le16 ea_length;		/* Byte size of the packed extended
				   attributes. */
	le16 need_ea_count;	/* The number of extended attributes which have
				   the NEED_EA bit set. */
	le32 ea_query_length;	/* Byte size of the buffer required to query
				   the extended attributes when calling
				   ZwQueryEaFile() in Winकरोws NT/2k. I.e. the
				   byte size of the unpacked extended
				   attributes. */
पूर्ण __attribute__ ((__packed__)) EA_INFORMATION;

/*
 * Extended attribute flags (8-bit).
 */
क्रमागत अणु
	NEED_EA	= 0x80		/* If set the file to which the EA beदीर्घs
				   cannot be पूर्णांकerpreted without understanding
				   the associates extended attributes. */
पूर्ण __attribute__ ((__packed__));

प्रकार u8 EA_FLAGS;

/*
 * Attribute: Extended attribute (EA) (0xe0).
 *
 * NOTE: Can be resident or non-resident.
 *
 * Like the attribute list and the index buffer list, the EA attribute value is
 * a sequence of EA_ATTR variable length records.
 */
प्रकार काष्ठा अणु
	le32 next_entry_offset;	/* Offset to the next EA_ATTR. */
	EA_FLAGS flags;		/* Flags describing the EA. */
	u8 ea_name_length;	/* Length of the name of the EA in bytes
				   excluding the '\0' byte terminator. */
	le16 ea_value_length;	/* Byte size of the EA's value. */
	u8 ea_name[0];		/* Name of the EA.  Note this is ASCII, not
				   Unicode and it is zero terminated. */
	u8 ea_value[0];		/* The value of the EA.  Immediately follows
				   the name. */
पूर्ण __attribute__ ((__packed__)) EA_ATTR;

/*
 * Attribute: Property set (0xf0).
 *
 * Intended to support Native Structure Storage (NSS) - a feature हटाओd from
 * NTFS 3.0 during beta testing.
 */
प्रकार काष्ठा अणु
	/* Irrelevant as feature unused. */
पूर्ण __attribute__ ((__packed__)) PROPERTY_SET;

/*
 * Attribute: Logged utility stream (0x100).
 *
 * NOTE: Can be resident or non-resident.
 *
 * Operations on this attribute are logged to the journal ($LogFile) like
 * normal metadata changes.
 *
 * Used by the Encrypting File System (EFS). All encrypted files have this
 * attribute with the name $EFS.
 */
प्रकार काष्ठा अणु
	/* Can be anything the creator chooses. */
	/* EFS uses it as follows: */
	// FIXME: Type this info, verअगरying it aदीर्घ the way. (AIA)
पूर्ण __attribute__ ((__packed__)) LOGGED_UTILITY_STREAM, EFS_ATTR;

#पूर्ण_अगर /* _LINUX_NTFS_LAYOUT_H */
