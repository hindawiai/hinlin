<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
   md_p.h : physical layout of Linux RAID devices
          Copyright (C) 1996-98 Ingo Molnar, Gadi Oxman
	  
   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
   
   You should have received a copy of the GNU General Public License
   (क्रम example /usr/src/linux/COPYING); अगर not, ग_लिखो to the Free
   Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  
*/

#अगर_अघोषित _MD_P_H
#घोषणा _MD_P_H

#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

/*
 * RAID superblock.
 *
 * The RAID superblock मुख्यtains some statistics on each RAID configuration.
 * Each real device in the RAID set contains it near the end of the device.
 * Some of the ideas are copied from the ext2fs implementation.
 *
 * We currently use 4096 bytes as follows:
 *
 *	word offset	function
 *
 *	   0  -    31	Constant generic RAID device inक्रमmation.
 *        32  -    63   Generic state inक्रमmation.
 *	  64  -   127	Personality specअगरic inक्रमmation.
 *	 128  -   511	12 32-words descriptors of the disks in the raid set.
 *	 512  -   911	Reserved.
 *	 912  -  1023	Disk specअगरic descriptor.
 */

/*
 * If x is the real device size in bytes, we वापस an apparent size of:
 *
 *	y = (x & ~(MD_RESERVED_BYTES - 1)) - MD_RESERVED_BYTES
 *
 * and place the 4kB superblock at offset y.
 */
#घोषणा MD_RESERVED_BYTES		(64 * 1024)
#घोषणा MD_RESERVED_SECTORS		(MD_RESERVED_BYTES / 512)

#घोषणा MD_NEW_SIZE_SECTORS(x)		((x & ~(MD_RESERVED_SECTORS - 1)) - MD_RESERVED_SECTORS)

#घोषणा MD_SB_BYTES			4096
#घोषणा MD_SB_WORDS			(MD_SB_BYTES / 4)
#घोषणा MD_SB_SECTORS			(MD_SB_BYTES / 512)

/*
 * The following are counted in 32-bit words
 */
#घोषणा	MD_SB_GENERIC_OFFSET		0
#घोषणा MD_SB_PERSONALITY_OFFSET	64
#घोषणा MD_SB_DISKS_OFFSET		128
#घोषणा MD_SB_DESCRIPTOR_OFFSET		992

#घोषणा MD_SB_GENERIC_CONSTANT_WORDS	32
#घोषणा MD_SB_GENERIC_STATE_WORDS	32
#घोषणा MD_SB_GENERIC_WORDS		(MD_SB_GENERIC_CONSTANT_WORDS + MD_SB_GENERIC_STATE_WORDS)
#घोषणा MD_SB_PERSONALITY_WORDS		64
#घोषणा MD_SB_DESCRIPTOR_WORDS		32
#घोषणा MD_SB_DISKS			27
#घोषणा MD_SB_DISKS_WORDS		(MD_SB_DISKS*MD_SB_DESCRIPTOR_WORDS)
#घोषणा MD_SB_RESERVED_WORDS		(1024 - MD_SB_GENERIC_WORDS - MD_SB_PERSONALITY_WORDS - MD_SB_DISKS_WORDS - MD_SB_DESCRIPTOR_WORDS)
#घोषणा MD_SB_EQUAL_WORDS		(MD_SB_GENERIC_WORDS + MD_SB_PERSONALITY_WORDS + MD_SB_DISKS_WORDS)

/*
 * Device "operational" state bits
 */
#घोषणा MD_DISK_FAULTY		0 /* disk is faulty / operational */
#घोषणा MD_DISK_ACTIVE		1 /* disk is running or spare disk */
#घोषणा MD_DISK_SYNC		2 /* disk is in sync with the raid set */
#घोषणा MD_DISK_REMOVED		3 /* disk is in sync with the raid set */
#घोषणा MD_DISK_CLUSTER_ADD     4 /* Initiate a disk add across the cluster
				   * For clustered enviroments only.
				   */
#घोषणा MD_DISK_CANDIDATE	5 /* disk is added as spare (local) until confirmed
				   * For clustered enviroments only.
				   */
#घोषणा MD_DISK_FAILFAST	10 /* Send REQ_FAILFAST अगर there are multiple
				    * devices available - and करोn't try to
				    * correct पढ़ो errors.
				    */

#घोषणा	MD_DISK_WRITEMOSTLY	9 /* disk is "write-mostly" is RAID1 config.
				   * पढ़ो requests will only be sent here in
				   * dire need
				   */
#घोषणा MD_DISK_JOURNAL		18 /* disk is used as the ग_लिखो journal in RAID-5/6 */

#घोषणा MD_DISK_ROLE_SPARE	0xffff
#घोषणा MD_DISK_ROLE_FAULTY	0xfffe
#घोषणा MD_DISK_ROLE_JOURNAL	0xfffd
#घोषणा MD_DISK_ROLE_MAX	0xff00 /* max value of regular disk role */

प्रकार काष्ठा mdp_device_descriptor_s अणु
	__u32 number;		/* 0 Device number in the entire set	      */
	__u32 major;		/* 1 Device major number		      */
	__u32 minor;		/* 2 Device minor number		      */
	__u32 raid_disk;	/* 3 The role of the device in the raid set   */
	__u32 state;		/* 4 Operational state			      */
	__u32 reserved[MD_SB_DESCRIPTOR_WORDS - 5];
पूर्ण mdp_disk_t;

#घोषणा MD_SB_MAGIC		0xa92b4efc

/*
 * Superblock state bits
 */
#घोषणा MD_SB_CLEAN		0
#घोषणा MD_SB_ERRORS		1

#घोषणा	MD_SB_CLUSTERED		5 /* MD is clustered */
#घोषणा	MD_SB_BITMAP_PRESENT	8 /* biपंचांगap may be present nearby */

/*
 * Notes:
 * - अगर an array is being reshaped (restriped) in order to change
 *   the number of active devices in the array, 'raid_disks' will be
 *   the larger of the old and new numbers.  'delta_disks' will
 *   be the "new - old".  So अगर +ve, raid_disks is the new value, and
 *   "raid_disks-delta_disks" is the old.  If -ve, raid_disks is the
 *   old value and "raid_disks+delta_disks" is the new (smaller) value.
 */


प्रकार काष्ठा mdp_superblock_s अणु
	/*
	 * Constant generic inक्रमmation
	 */
	__u32 md_magic;		/*  0 MD identअगरier 			      */
	__u32 major_version;	/*  1 major version to which the set conक्रमms */
	__u32 minor_version;	/*  2 minor version ...			      */
	__u32 patch_version;	/*  3 patchlevel version ...		      */
	__u32 gvalid_words;	/*  4 Number of used words in this section    */
	__u32 set_uuid0;	/*  5 Raid set identअगरier		      */
	__u32 स_समय;		/*  6 Creation समय			      */
	__u32 level;		/*  7 Raid personality			      */
	__u32 size;		/*  8 Apparent size of each inभागidual disk   */
	__u32 nr_disks;		/*  9 total disks in the raid set	      */
	__u32 raid_disks;	/* 10 disks in a fully functional raid set    */
	__u32 md_minor;		/* 11 preferred MD minor device number	      */
	__u32 not_persistent;	/* 12 करोes it have a persistent superblock    */
	__u32 set_uuid1;	/* 13 Raid set identअगरier #2		      */
	__u32 set_uuid2;	/* 14 Raid set identअगरier #3		      */
	__u32 set_uuid3;	/* 15 Raid set identअगरier #4		      */
	__u32 gstate_creserved[MD_SB_GENERIC_CONSTANT_WORDS - 16];

	/*
	 * Generic state inक्रमmation
	 */
	__u32 uसमय;		/*  0 Superblock update समय		      */
	__u32 state;		/*  1 State bits (clean, ...)		      */
	__u32 active_disks;	/*  2 Number of currently active disks	      */
	__u32 working_disks;	/*  3 Number of working disks		      */
	__u32 failed_disks;	/*  4 Number of failed disks		      */
	__u32 spare_disks;	/*  5 Number of spare disks		      */
	__u32 sb_csum;		/*  6 checksum of the whole superblock        */
#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
	__u32 events_hi;	/*  7 high-order of superblock update count   */
	__u32 events_lo;	/*  8 low-order of superblock update count    */
	__u32 cp_events_hi;	/*  9 high-order of checkpoपूर्णांक update count   */
	__u32 cp_events_lo;	/* 10 low-order of checkpoपूर्णांक update count    */
#या_अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
	__u32 events_lo;	/*  7 low-order of superblock update count    */
	__u32 events_hi;	/*  8 high-order of superblock update count   */
	__u32 cp_events_lo;	/*  9 low-order of checkpoपूर्णांक update count    */
	__u32 cp_events_hi;	/* 10 high-order of checkpoपूर्णांक update count   */
#अन्यथा
#त्रुटि unspecअगरied endianness
#पूर्ण_अगर
	__u32 recovery_cp;	/* 11 recovery checkpoपूर्णांक sector count	      */
	/* There are only valid क्रम minor_version > 90 */
	__u64 reshape_position;	/* 12,13 next address in array-space क्रम reshape */
	__u32 new_level;	/* 14 new level we are reshaping to	      */
	__u32 delta_disks;	/* 15 change in number of raid_disks	      */
	__u32 new_layout;	/* 16 new layout			      */
	__u32 new_chunk;	/* 17 new chunk size (bytes)		      */
	__u32 gstate_sreserved[MD_SB_GENERIC_STATE_WORDS - 18];

	/*
	 * Personality inक्रमmation
	 */
	__u32 layout;		/*  0 the array's physical layout	      */
	__u32 chunk_size;	/*  1 chunk size in bytes		      */
	__u32 root_pv;		/*  2 LV root PV */
	__u32 root_block;	/*  3 LV root block */
	__u32 pstate_reserved[MD_SB_PERSONALITY_WORDS - 4];

	/*
	 * Disks inक्रमmation
	 */
	mdp_disk_t disks[MD_SB_DISKS];

	/*
	 * Reserved
	 */
	__u32 reserved[MD_SB_RESERVED_WORDS];

	/*
	 * Active descriptor
	 */
	mdp_disk_t this_disk;

पूर्ण mdp_super_t;

अटल अंतरभूत __u64 md_event(mdp_super_t *sb) अणु
	__u64 ev = sb->events_hi;
	वापस (ev<<32)| sb->events_lo;
पूर्ण

#घोषणा MD_SUPERBLOCK_1_TIME_SEC_MASK ((1ULL<<40) - 1)

/*
 * The version-1 superblock :
 * All numeric fields are little-endian.
 *
 * total size: 256 bytes plus 2 per device.
 *  1K allows 384 devices.
 */
काष्ठा mdp_superblock_1 अणु
	/* स्थिरant array inक्रमmation - 128 bytes */
	__le32	magic;		/* MD_SB_MAGIC: 0xa92b4efc - little endian */
	__le32	major_version;	/* 1 */
	__le32	feature_map;	/* bit 0 set अगर 'bitmap_offset' is meaningful */
	__le32	pad0;		/* always set to 0 when writing */

	__u8	set_uuid[16];	/* user-space generated. */
	अक्षर	set_name[32];	/* set and पूर्णांकerpreted by user-space */

	__le64	स_समय;		/* lo 40 bits are seconds, top 24 are microseconds or 0*/
	__le32	level;		/* -4 (multipath), -1 (linear), 0,1,4,5 */
	__le32	layout;		/* only क्रम raid5 and raid10 currently */
	__le64	size;		/* used size of component devices, in 512byte sectors */

	__le32	chunksize;	/* in 512byte sectors */
	__le32	raid_disks;
	जोड़ अणु
		__le32	biपंचांगap_offset;	/* sectors after start of superblock that biपंचांगap starts
					 * NOTE: चिन्हित, so biपंचांगap can be beक्रमe superblock
					 * only meaningful of feature_map[0] is set.
					 */

		/* only meaningful when feature_map[MD_FEATURE_PPL] is set */
		काष्ठा अणु
			__le16 offset; /* sectors from start of superblock that ppl starts (चिन्हित) */
			__le16 size; /* ppl size in sectors */
		पूर्ण ppl;
	पूर्ण;

	/* These are only valid with feature bit '4' */
	__le32	new_level;	/* new level we are reshaping to		*/
	__le64	reshape_position;	/* next address in array-space क्रम reshape */
	__le32	delta_disks;	/* change in number of raid_disks		*/
	__le32	new_layout;	/* new layout					*/
	__le32	new_chunk;	/* new chunk size (512byte sectors)		*/
	__le32  new_offset;	/* चिन्हित number to add to data_offset in new
				 * layout.  0 == no-change.  This can be
				 * dअगरferent on each device in the array.
				 */

	/* स्थिरant this-device inक्रमmation - 64 bytes */
	__le64	data_offset;	/* sector start of data, often 0 */
	__le64	data_size;	/* sectors in this device that can be used क्रम data */
	__le64	super_offset;	/* sector start of this superblock */
	जोड़ अणु
		__le64	recovery_offset;/* sectors beक्रमe this offset (from data_offset) have been recovered */
		__le64	journal_tail;/* journal tail of journal device (from data_offset) */
	पूर्ण;
	__le32	dev_number;	/* permanent identअगरier of this  device - not role in raid */
	__le32	cnt_corrected_पढ़ो; /* number of पढ़ो errors that were corrected by re-writing */
	__u8	device_uuid[16]; /* user-space setable, ignored by kernel */
	__u8	devflags;	/* per-device flags.  Only two defined...*/
#घोषणा	WriteMostly1	1	/* mask क्रम ग_लिखोmostly flag in above */
#घोषणा	FailFast1	2	/* Should aव्योम retries and fixups and just fail */
	/* Bad block log.  If there are any bad blocks the feature flag is set.
	 * If offset and size are non-zero, that space is reserved and available
	 */
	__u8	bblog_shअगरt;	/* shअगरt from sectors to block size */
	__le16	bblog_size;	/* number of sectors reserved क्रम list */
	__le32	bblog_offset;	/* sector offset from superblock to bblog,
				 * चिन्हित - not अचिन्हित */

	/* array state inक्रमmation - 64 bytes */
	__le64	uसमय;		/* 40 bits second, 24 bits microseconds */
	__le64	events;		/* incremented when superblock updated */
	__le64	resync_offset;	/* data beक्रमe this offset (from data_offset) known to be in sync */
	__le32	sb_csum;	/* checksum up to devs[max_dev] */
	__le32	max_dev;	/* size of devs[] array to consider */
	__u8	pad3[64-32];	/* set to 0 when writing */

	/* device state inक्रमmation. Indexed by dev_number.
	 * 2 bytes per device
	 * Note there are no per-device state flags. State inक्रमmation is rolled
	 * पूर्णांकo the 'roles' value.  If a device is spare or faulty, then it doesn't
	 * have a meaningful role.
	 */
	__le16	dev_roles[0];	/* role in array, or 0xffff क्रम a spare, or 0xfffe क्रम faulty */
पूर्ण;

/* feature_map bits */
#घोषणा MD_FEATURE_BITMAP_OFFSET	1
#घोषणा	MD_FEATURE_RECOVERY_OFFSET	2 /* recovery_offset is present and
					   * must be honoured
					   */
#घोषणा	MD_FEATURE_RESHAPE_ACTIVE	4
#घोषणा	MD_FEATURE_BAD_BLOCKS		8 /* badblock list is not empty */
#घोषणा	MD_FEATURE_REPLACEMENT		16 /* This device is replacing an
					    * active device with same 'role'.
					    * 'recovery_offset' is also set.
					    */
#घोषणा	MD_FEATURE_RESHAPE_BACKWARDS	32 /* Reshape करोesn't change number
					    * of devices, but is going
					    * backwards anyway.
					    */
#घोषणा	MD_FEATURE_NEW_OFFSET		64 /* new_offset must be honoured */
#घोषणा	MD_FEATURE_RECOVERY_BITMAP	128 /* recovery that is happening
					     * is guided by biपंचांगap.
					     */
#घोषणा	MD_FEATURE_CLUSTERED		256 /* clustered MD */
#घोषणा	MD_FEATURE_JOURNAL		512 /* support ग_लिखो cache */
#घोषणा	MD_FEATURE_PPL			1024 /* support PPL */
#घोषणा	MD_FEATURE_MULTIPLE_PPLS	2048 /* support क्रम multiple PPLs */
#घोषणा	MD_FEATURE_RAID0_LAYOUT		4096 /* layout is meaningful क्रम RAID0 */
#घोषणा	MD_FEATURE_ALL			(MD_FEATURE_BITMAP_OFFSET	\
					|MD_FEATURE_RECOVERY_OFFSET	\
					|MD_FEATURE_RESHAPE_ACTIVE	\
					|MD_FEATURE_BAD_BLOCKS		\
					|MD_FEATURE_REPLACEMENT		\
					|MD_FEATURE_RESHAPE_BACKWARDS	\
					|MD_FEATURE_NEW_OFFSET		\
					|MD_FEATURE_RECOVERY_BITMAP	\
					|MD_FEATURE_CLUSTERED		\
					|MD_FEATURE_JOURNAL		\
					|MD_FEATURE_PPL			\
					|MD_FEATURE_MULTIPLE_PPLS	\
					|MD_FEATURE_RAID0_LAYOUT	\
					)

काष्ठा r5l_payload_header अणु
	__le16 type;
	__le16 flags;
पूर्ण __attribute__ ((__packed__));

क्रमागत r5l_payload_type अणु
	R5LOG_PAYLOAD_DATA = 0,
	R5LOG_PAYLOAD_PARITY = 1,
	R5LOG_PAYLOAD_FLUSH = 2,
पूर्ण;

काष्ठा r5l_payload_data_parity अणु
	काष्ठा r5l_payload_header header;
	__le32 size;		/* sector. data/parity size. each 4k
				 * has a checksum */
	__le64 location;	/* sector. For data, it's raid sector. For
				 * parity, it's stripe sector */
	__le32 checksum[];
पूर्ण __attribute__ ((__packed__));

क्रमागत r5l_payload_data_parity_flag अणु
	R5LOG_PAYLOAD_FLAG_DISCARD = 1, /* payload is discard */
	/*
	 * RESHAPED/RESHAPING is only set when there is reshape activity. Note,
	 * both data/parity of a stripe should have the same flag set
	 *
	 * RESHAPED: reshape is running, and this stripe finished reshape
	 * RESHAPING: reshape is running, and this stripe isn't reshaped
	 */
	R5LOG_PAYLOAD_FLAG_RESHAPED = 2,
	R5LOG_PAYLOAD_FLAG_RESHAPING = 3,
पूर्ण;

काष्ठा r5l_payload_flush अणु
	काष्ठा r5l_payload_header header;
	__le32 size; /* flush_stripes size, bytes */
	__le64 flush_stripes[];
पूर्ण __attribute__ ((__packed__));

क्रमागत r5l_payload_flush_flag अणु
	R5LOG_PAYLOAD_FLAG_FLUSH_STRIPE = 1, /* data represents whole stripe */
पूर्ण;

काष्ठा r5l_meta_block अणु
	__le32 magic;
	__le32 checksum;
	__u8 version;
	__u8 __zero_pading_1;
	__le16 __zero_pading_2;
	__le32 meta_size; /* whole size of the block */

	__le64 seq;
	__le64 position; /* sector, start from rdev->data_offset, current position */
	काष्ठा r5l_payload_header payloads[];
पूर्ण __attribute__ ((__packed__));

#घोषणा R5LOG_VERSION 0x1
#घोषणा R5LOG_MAGIC 0x6433c509

काष्ठा ppl_header_entry अणु
	__le64 data_sector;	/* raid sector of the new data */
	__le32 pp_size;		/* length of partial parity */
	__le32 data_size;	/* length of data */
	__le32 parity_disk;	/* member disk containing parity */
	__le32 checksum;	/* checksum of partial parity data क्रम this
				 * entry (~crc32c) */
पूर्ण __attribute__ ((__packed__));

#घोषणा PPL_HEADER_SIZE 4096
#घोषणा PPL_HDR_RESERVED 512
#घोषणा PPL_HDR_ENTRY_SPACE \
	(PPL_HEADER_SIZE - PPL_HDR_RESERVED - 4 * माप(__le32) - माप(__le64))
#घोषणा PPL_HDR_MAX_ENTRIES \
	(PPL_HDR_ENTRY_SPACE / माप(काष्ठा ppl_header_entry))

काष्ठा ppl_header अणु
	__u8 reserved[PPL_HDR_RESERVED];/* reserved space, fill with 0xff */
	__le32 signature;		/* signature (family number of volume) */
	__le32 padding;			/* zero pad */
	__le64 generation;		/* generation number of the header */
	__le32 entries_count;		/* number of entries in entry array */
	__le32 checksum;		/* checksum of the header (~crc32c) */
	काष्ठा ppl_header_entry entries[PPL_HDR_MAX_ENTRIES];
पूर्ण __attribute__ ((__packed__));

#पूर्ण_अगर
