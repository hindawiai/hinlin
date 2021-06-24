<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public
 * License v2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public
 * License aदीर्घ with this program; अगर not, ग_लिखो to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 021110-1307, USA.
 */

#अगर_अघोषित _UAPI_LINUX_BTRFS_H
#घोषणा _UAPI_LINUX_BTRFS_H
#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा BTRFS_IOCTL_MAGIC 0x94
#घोषणा BTRFS_VOL_NAME_MAX 255
#घोषणा BTRFS_LABEL_SIZE 256

/* this should be 4k */
#घोषणा BTRFS_PATH_NAME_MAX 4087
काष्ठा btrfs_ioctl_vol_args अणु
	__s64 fd;
	अक्षर name[BTRFS_PATH_NAME_MAX + 1];
पूर्ण;

#घोषणा BTRFS_DEVICE_PATH_NAME_MAX	1024
#घोषणा BTRFS_SUBVOL_NAME_MAX 		4039

#अगर_अघोषित __KERNEL__
/* Deprecated since 5.7 */
# define BTRFS_SUBVOL_CREATE_ASYNC	(1ULL << 0)
#पूर्ण_अगर
#घोषणा BTRFS_SUBVOL_RDONLY		(1ULL << 1)
#घोषणा BTRFS_SUBVOL_QGROUP_INHERIT	(1ULL << 2)

#घोषणा BTRFS_DEVICE_SPEC_BY_ID		(1ULL << 3)

#घोषणा BTRFS_SUBVOL_SPEC_BY_ID	(1ULL << 4)

#घोषणा BTRFS_VOL_ARG_V2_FLAGS_SUPPORTED		\
			(BTRFS_SUBVOL_RDONLY |		\
			BTRFS_SUBVOL_QGROUP_INHERIT |	\
			BTRFS_DEVICE_SPEC_BY_ID |	\
			BTRFS_SUBVOL_SPEC_BY_ID)

#घोषणा BTRFS_FSID_SIZE 16
#घोषणा BTRFS_UUID_SIZE 16
#घोषणा BTRFS_UUID_UNPARSED_SIZE	37

/*
 * flags definition क्रम qgroup limits
 *
 * Used by:
 * काष्ठा btrfs_qgroup_limit.flags
 * काष्ठा btrfs_qgroup_limit_item.flags
 */
#घोषणा BTRFS_QGROUP_LIMIT_MAX_RFER	(1ULL << 0)
#घोषणा BTRFS_QGROUP_LIMIT_MAX_EXCL	(1ULL << 1)
#घोषणा BTRFS_QGROUP_LIMIT_RSV_RFER	(1ULL << 2)
#घोषणा BTRFS_QGROUP_LIMIT_RSV_EXCL	(1ULL << 3)
#घोषणा BTRFS_QGROUP_LIMIT_RFER_CMPR	(1ULL << 4)
#घोषणा BTRFS_QGROUP_LIMIT_EXCL_CMPR	(1ULL << 5)

काष्ठा btrfs_qgroup_limit अणु
	__u64	flags;
	__u64	max_rfer;
	__u64	max_excl;
	__u64	rsv_rfer;
	__u64	rsv_excl;
पूर्ण;

/*
 * flags definition क्रम qgroup inheritance
 *
 * Used by:
 * काष्ठा btrfs_qgroup_inherit.flags
 */
#घोषणा BTRFS_QGROUP_INHERIT_SET_LIMITS	(1ULL << 0)

काष्ठा btrfs_qgroup_inherit अणु
	__u64	flags;
	__u64	num_qgroups;
	__u64	num_ref_copies;
	__u64	num_excl_copies;
	काष्ठा btrfs_qgroup_limit lim;
	__u64	qgroups[0];
पूर्ण;

काष्ठा btrfs_ioctl_qgroup_limit_args अणु
	__u64	qgroupid;
	काष्ठा btrfs_qgroup_limit lim;
पूर्ण;

/*
 * Arguments क्रम specअगरication of subvolumes or devices, supporting by-name or
 * by-id and flags
 *
 * The set of supported flags depends on the ioctl
 *
 * BTRFS_SUBVOL_RDONLY is also provided/consumed by the following ioctls:
 * - BTRFS_IOC_SUBVOL_GETFLAGS
 * - BTRFS_IOC_SUBVOL_SETFLAGS
 */

/* Supported flags क्रम BTRFS_IOC_RM_DEV_V2 */
#घोषणा BTRFS_DEVICE_REMOVE_ARGS_MASK					\
	(BTRFS_DEVICE_SPEC_BY_ID)

/* Supported flags क्रम BTRFS_IOC_SNAP_CREATE_V2 and BTRFS_IOC_SUBVOL_CREATE_V2 */
#घोषणा BTRFS_SUBVOL_CREATE_ARGS_MASK					\
	 (BTRFS_SUBVOL_RDONLY |						\
	 BTRFS_SUBVOL_QGROUP_INHERIT)

/* Supported flags क्रम BTRFS_IOC_SNAP_DESTROY_V2 */
#घोषणा BTRFS_SUBVOL_DELETE_ARGS_MASK					\
	(BTRFS_SUBVOL_SPEC_BY_ID)

काष्ठा btrfs_ioctl_vol_args_v2 अणु
	__s64 fd;
	__u64 transid;
	__u64 flags;
	जोड़ अणु
		काष्ठा अणु
			__u64 size;
			काष्ठा btrfs_qgroup_inherit __user *qgroup_inherit;
		पूर्ण;
		__u64 unused[4];
	पूर्ण;
	जोड़ अणु
		अक्षर name[BTRFS_SUBVOL_NAME_MAX + 1];
		__u64 devid;
		__u64 subvolid;
	पूर्ण;
पूर्ण;

/*
 * काष्ठाure to report errors and progress to userspace, either as a
 * result of a finished scrub, a canceled scrub or a progress inquiry
 */
काष्ठा btrfs_scrub_progress अणु
	__u64 data_extents_scrubbed;	/* # of data extents scrubbed */
	__u64 tree_extents_scrubbed;	/* # of tree extents scrubbed */
	__u64 data_bytes_scrubbed;	/* # of data bytes scrubbed */
	__u64 tree_bytes_scrubbed;	/* # of tree bytes scrubbed */
	__u64 पढ़ो_errors;		/* # of पढ़ो errors encountered (EIO) */
	__u64 csum_errors;		/* # of failed csum checks */
	__u64 verअगरy_errors;		/* # of occurences, where the metadata
					 * of a tree block did not match the
					 * expected values, like generation or
					 * logical */
	__u64 no_csum;			/* # of 4k data block क्रम which no csum
					 * is present, probably the result of
					 * data written with nodatasum */
	__u64 csum_discards;		/* # of csum क्रम which no data was found
					 * in the extent tree. */
	__u64 super_errors;		/* # of bad super blocks encountered */
	__u64 दो_स्मृति_errors;		/* # of पूर्णांकernal kदो_स्मृति errors. These
					 * will likely cause an incomplete
					 * scrub */
	__u64 uncorrectable_errors;	/* # of errors where either no पूर्णांकact
					 * copy was found or the ग_लिखोback
					 * failed */
	__u64 corrected_errors;		/* # of errors corrected */
	__u64 last_physical;		/* last physical address scrubbed. In
					 * हाल a scrub was पातed, this can
					 * be used to restart the scrub */
	__u64 unverअगरied_errors;	/* # of occurences where a पढ़ो क्रम a
					 * full (64k) bio failed, but the re-
					 * check succeeded क्रम each 4k piece.
					 * Intermittent error. */
पूर्ण;

#घोषणा BTRFS_SCRUB_READONLY	1
काष्ठा btrfs_ioctl_scrub_args अणु
	__u64 devid;				/* in */
	__u64 start;				/* in */
	__u64 end;				/* in */
	__u64 flags;				/* in */
	काष्ठा btrfs_scrub_progress progress;	/* out */
	/* pad to 1k */
	__u64 unused[(1024-32-माप(काष्ठा btrfs_scrub_progress))/8];
पूर्ण;

#घोषणा BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_ALWAYS	0
#घोषणा BTRFS_IOCTL_DEV_REPLACE_CONT_READING_FROM_SRCDEV_MODE_AVOID	1
काष्ठा btrfs_ioctl_dev_replace_start_params अणु
	__u64 srcdevid;	/* in, अगर 0, use srcdev_name instead */
	__u64 cont_पढ़ोing_from_srcdev_mode;	/* in, see #घोषणा
						 * above */
	__u8 srcdev_name[BTRFS_DEVICE_PATH_NAME_MAX + 1];	/* in */
	__u8 tgtdev_name[BTRFS_DEVICE_PATH_NAME_MAX + 1];	/* in */
पूर्ण;

#घोषणा BTRFS_IOCTL_DEV_REPLACE_STATE_NEVER_STARTED	0
#घोषणा BTRFS_IOCTL_DEV_REPLACE_STATE_STARTED		1
#घोषणा BTRFS_IOCTL_DEV_REPLACE_STATE_FINISHED		2
#घोषणा BTRFS_IOCTL_DEV_REPLACE_STATE_CANCELED		3
#घोषणा BTRFS_IOCTL_DEV_REPLACE_STATE_SUSPENDED		4
काष्ठा btrfs_ioctl_dev_replace_status_params अणु
	__u64 replace_state;	/* out, see #घोषणा above */
	__u64 progress_1000;	/* out, 0 <= x <= 1000 */
	__u64 समय_started;	/* out, seconds since 1-Jan-1970 */
	__u64 समय_stopped;	/* out, seconds since 1-Jan-1970 */
	__u64 num_ग_लिखो_errors;	/* out */
	__u64 num_uncorrectable_पढ़ो_errors;	/* out */
पूर्ण;

#घोषणा BTRFS_IOCTL_DEV_REPLACE_CMD_START			0
#घोषणा BTRFS_IOCTL_DEV_REPLACE_CMD_STATUS			1
#घोषणा BTRFS_IOCTL_DEV_REPLACE_CMD_CANCEL			2
#घोषणा BTRFS_IOCTL_DEV_REPLACE_RESULT_NO_ERROR			0
#घोषणा BTRFS_IOCTL_DEV_REPLACE_RESULT_NOT_STARTED		1
#घोषणा BTRFS_IOCTL_DEV_REPLACE_RESULT_ALREADY_STARTED		2
#घोषणा BTRFS_IOCTL_DEV_REPLACE_RESULT_SCRUB_INPROGRESS		3
काष्ठा btrfs_ioctl_dev_replace_args अणु
	__u64 cmd;	/* in */
	__u64 result;	/* out */

	जोड़ अणु
		काष्ठा btrfs_ioctl_dev_replace_start_params start;
		काष्ठा btrfs_ioctl_dev_replace_status_params status;
	पूर्ण;	/* in/out */

	__u64 spare[64];
पूर्ण;

काष्ठा btrfs_ioctl_dev_info_args अणु
	__u64 devid;				/* in/out */
	__u8 uuid[BTRFS_UUID_SIZE];		/* in/out */
	__u64 bytes_used;			/* out */
	__u64 total_bytes;			/* out */
	__u64 unused[379];			/* pad to 4k */
	__u8 path[BTRFS_DEVICE_PATH_NAME_MAX];	/* out */
पूर्ण;

/*
 * Retrieve inक्रमmation about the fileप्रणाली
 */

/* Request inक्रमmation about checksum type and size */
#घोषणा BTRFS_FS_INFO_FLAG_CSUM_INFO			(1 << 0)

/* Request inक्रमmation about fileप्रणाली generation */
#घोषणा BTRFS_FS_INFO_FLAG_GENERATION			(1 << 1)
/* Request inक्रमmation about fileप्रणाली metadata UUID */
#घोषणा BTRFS_FS_INFO_FLAG_METADATA_UUID		(1 << 2)

काष्ठा btrfs_ioctl_fs_info_args अणु
	__u64 max_id;				/* out */
	__u64 num_devices;			/* out */
	__u8 fsid[BTRFS_FSID_SIZE];		/* out */
	__u32 nodesize;				/* out */
	__u32 sectorsize;			/* out */
	__u32 clone_alignment;			/* out */
	/* See BTRFS_FS_INFO_FLAG_* */
	__u16 csum_type;			/* out */
	__u16 csum_size;			/* out */
	__u64 flags;				/* in/out */
	__u64 generation;			/* out */
	__u8 metadata_uuid[BTRFS_FSID_SIZE];	/* out */
	__u8 reserved[944];			/* pad to 1k */
पूर्ण;

/*
 * feature flags
 *
 * Used by:
 * काष्ठा btrfs_ioctl_feature_flags
 */
#घोषणा BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE		(1ULL << 0)
/*
 * Older kernels (< 4.9) on big-endian प्रणालीs produced broken मुक्त space tree
 * biपंचांगaps, and btrfs-progs also used to corrupt the मुक्त space tree (versions
 * < 4.7.3).  If this bit is clear, then the मुक्त space tree cannot be trusted.
 * btrfs-progs can also पूर्णांकentionally clear this bit to ask the kernel to
 * rebuild the मुक्त space tree, however this might not work on older kernels
 * that करो not know about this bit. If not sure, clear the cache manually on
 * first mount when booting older kernel versions.
 */
#घोषणा BTRFS_FEATURE_COMPAT_RO_FREE_SPACE_TREE_VALID	(1ULL << 1)

#घोषणा BTRFS_FEATURE_INCOMPAT_MIXED_BACKREF	(1ULL << 0)
#घोषणा BTRFS_FEATURE_INCOMPAT_DEFAULT_SUBVOL	(1ULL << 1)
#घोषणा BTRFS_FEATURE_INCOMPAT_MIXED_GROUPS	(1ULL << 2)
#घोषणा BTRFS_FEATURE_INCOMPAT_COMPRESS_LZO	(1ULL << 3)
#घोषणा BTRFS_FEATURE_INCOMPAT_COMPRESS_ZSTD	(1ULL << 4)

/*
 * older kernels tried to करो bigger metadata blocks, but the
 * code was pretty buggy.  Lets not let them try anymore.
 */
#घोषणा BTRFS_FEATURE_INCOMPAT_BIG_METADATA	(1ULL << 5)

#घोषणा BTRFS_FEATURE_INCOMPAT_EXTENDED_IREF	(1ULL << 6)
#घोषणा BTRFS_FEATURE_INCOMPAT_RAID56		(1ULL << 7)
#घोषणा BTRFS_FEATURE_INCOMPAT_SKINNY_METADATA	(1ULL << 8)
#घोषणा BTRFS_FEATURE_INCOMPAT_NO_HOLES		(1ULL << 9)
#घोषणा BTRFS_FEATURE_INCOMPAT_METADATA_UUID	(1ULL << 10)
#घोषणा BTRFS_FEATURE_INCOMPAT_RAID1C34		(1ULL << 11)
#घोषणा BTRFS_FEATURE_INCOMPAT_ZONED		(1ULL << 12)

काष्ठा btrfs_ioctl_feature_flags अणु
	__u64 compat_flags;
	__u64 compat_ro_flags;
	__u64 incompat_flags;
पूर्ण;

/* balance control ioctl modes */
#घोषणा BTRFS_BALANCE_CTL_PAUSE		1
#घोषणा BTRFS_BALANCE_CTL_CANCEL	2

/*
 * this is packed, because it should be exactly the same as its disk
 * byte order counterpart (काष्ठा btrfs_disk_balance_args)
 */
काष्ठा btrfs_balance_args अणु
	__u64 profiles;
	जोड़ अणु
		__u64 usage;
		काष्ठा अणु
			__u32 usage_min;
			__u32 usage_max;
		पूर्ण;
	पूर्ण;
	__u64 devid;
	__u64 pstart;
	__u64 pend;
	__u64 vstart;
	__u64 vend;

	__u64 target;

	__u64 flags;

	/*
	 * BTRFS_BALANCE_ARGS_LIMIT with value 'limit'
	 * BTRFS_BALANCE_ARGS_LIMIT_RANGE - the extend version can use minimum
	 * and maximum
	 */
	जोड़ अणु
		__u64 limit;		/* limit number of processed chunks */
		काष्ठा अणु
			__u32 limit_min;
			__u32 limit_max;
		पूर्ण;
	पूर्ण;

	/*
	 * Process chunks that cross stripes_min..stripes_max devices,
	 * BTRFS_BALANCE_ARGS_STRIPES_RANGE
	 */
	__u32 stripes_min;
	__u32 stripes_max;

	__u64 unused[6];
पूर्ण __attribute__ ((__packed__));

/* report balance progress to userspace */
काष्ठा btrfs_balance_progress अणु
	__u64 expected;		/* estimated # of chunks that will be
				 * relocated to fulfill the request */
	__u64 considered;	/* # of chunks we have considered so far */
	__u64 completed;	/* # of chunks relocated so far */
पूर्ण;

/*
 * flags definition क्रम balance
 *
 * Restriper's general type filter
 *
 * Used by:
 * btrfs_ioctl_balance_args.flags
 * btrfs_balance_control.flags (पूर्णांकernal)
 */
#घोषणा BTRFS_BALANCE_DATA		(1ULL << 0)
#घोषणा BTRFS_BALANCE_SYSTEM		(1ULL << 1)
#घोषणा BTRFS_BALANCE_METADATA		(1ULL << 2)

#घोषणा BTRFS_BALANCE_TYPE_MASK		(BTRFS_BALANCE_DATA |	    \
					 BTRFS_BALANCE_SYSTEM |	    \
					 BTRFS_BALANCE_METADATA)

#घोषणा BTRFS_BALANCE_FORCE		(1ULL << 3)
#घोषणा BTRFS_BALANCE_RESUME		(1ULL << 4)

/*
 * flags definitions क्रम per-type balance args
 *
 * Balance filters
 *
 * Used by:
 * काष्ठा btrfs_balance_args
 */
#घोषणा BTRFS_BALANCE_ARGS_PROखाताS	(1ULL << 0)
#घोषणा BTRFS_BALANCE_ARGS_USAGE	(1ULL << 1)
#घोषणा BTRFS_BALANCE_ARGS_DEVID	(1ULL << 2)
#घोषणा BTRFS_BALANCE_ARGS_DRANGE	(1ULL << 3)
#घोषणा BTRFS_BALANCE_ARGS_VRANGE	(1ULL << 4)
#घोषणा BTRFS_BALANCE_ARGS_LIMIT	(1ULL << 5)
#घोषणा BTRFS_BALANCE_ARGS_LIMIT_RANGE	(1ULL << 6)
#घोषणा BTRFS_BALANCE_ARGS_STRIPES_RANGE (1ULL << 7)
#घोषणा BTRFS_BALANCE_ARGS_USAGE_RANGE	(1ULL << 10)

#घोषणा BTRFS_BALANCE_ARGS_MASK			\
	(BTRFS_BALANCE_ARGS_PROखाताS |		\
	 BTRFS_BALANCE_ARGS_USAGE |		\
	 BTRFS_BALANCE_ARGS_DEVID | 		\
	 BTRFS_BALANCE_ARGS_DRANGE |		\
	 BTRFS_BALANCE_ARGS_VRANGE |		\
	 BTRFS_BALANCE_ARGS_LIMIT |		\
	 BTRFS_BALANCE_ARGS_LIMIT_RANGE |	\
	 BTRFS_BALANCE_ARGS_STRIPES_RANGE |	\
	 BTRFS_BALANCE_ARGS_USAGE_RANGE)

/*
 * Profile changing flags.  When SOFT is set we won't relocate chunk अगर
 * it alपढ़ोy has the target profile (even though it may be
 * half-filled).
 */
#घोषणा BTRFS_BALANCE_ARGS_CONVERT	(1ULL << 8)
#घोषणा BTRFS_BALANCE_ARGS_SOFT		(1ULL << 9)


/*
 * flags definition क्रम balance state
 *
 * Used by:
 * काष्ठा btrfs_ioctl_balance_args.state
 */
#घोषणा BTRFS_BALANCE_STATE_RUNNING	(1ULL << 0)
#घोषणा BTRFS_BALANCE_STATE_PAUSE_REQ	(1ULL << 1)
#घोषणा BTRFS_BALANCE_STATE_CANCEL_REQ	(1ULL << 2)

काष्ठा btrfs_ioctl_balance_args अणु
	__u64 flags;				/* in/out */
	__u64 state;				/* out */

	काष्ठा btrfs_balance_args data;		/* in/out */
	काष्ठा btrfs_balance_args meta;		/* in/out */
	काष्ठा btrfs_balance_args sys;		/* in/out */

	काष्ठा btrfs_balance_progress stat;	/* out */

	__u64 unused[72];			/* pad to 1k */
पूर्ण;

#घोषणा BTRFS_INO_LOOKUP_PATH_MAX 4080
काष्ठा btrfs_ioctl_ino_lookup_args अणु
	__u64 treeid;
	__u64 objectid;
	अक्षर name[BTRFS_INO_LOOKUP_PATH_MAX];
पूर्ण;

#घोषणा BTRFS_INO_LOOKUP_USER_PATH_MAX (4080 - BTRFS_VOL_NAME_MAX - 1)
काष्ठा btrfs_ioctl_ino_lookup_user_args अणु
	/* in, inode number containing the subvolume of 'subvolid' */
	__u64 dirid;
	/* in */
	__u64 treeid;
	/* out, name of the subvolume of 'treeid' */
	अक्षर name[BTRFS_VOL_NAME_MAX + 1];
	/*
	 * out, स्थिरructed path from the directory with which the ioctl is
	 * called to dirid
	 */
	अक्षर path[BTRFS_INO_LOOKUP_USER_PATH_MAX];
पूर्ण;

/* Search criteria क्रम the btrfs SEARCH ioctl family. */
काष्ठा btrfs_ioctl_search_key अणु
	/*
	 * The tree we're searching in. 1 is the tree of tree roots, 2 is the
	 * extent tree, etc...
	 *
	 * A special tree_id value of 0 will cause a search in the subvolume
	 * tree that the inode which is passed to the ioctl is part of.
	 */
	__u64 tree_id;		/* in */

	/*
	 * When करोing a tree search, we're actually taking a slice from a
	 * linear search space of 136-bit keys.
	 *
	 * A full 136-bit tree key is composed as:
	 *   (objectid << 72) + (type << 64) + offset
	 *
	 * The inभागidual min and max values क्रम objectid, type and offset
	 * define the min_key and max_key values क्रम the search range. All
	 * metadata items with a key in the पूर्णांकerval [min_key, max_key] will be
	 * वापसed.
	 *
	 * Additionally, we can filter the items वापसed on transaction id of
	 * the metadata block they're stored in by specअगरying a transid range.
	 * Be aware that this transaction id only denotes when the metadata
	 * page that currently contains the item got written the last समय as
	 * result of a COW operation.  The number करोes not have any meaning
	 * related to the transaction in which an inभागidual item that is being
	 * वापसed was created or changed.
	 */
	__u64 min_objectid;	/* in */
	__u64 max_objectid;	/* in */
	__u64 min_offset;	/* in */
	__u64 max_offset;	/* in */
	__u64 min_transid;	/* in */
	__u64 max_transid;	/* in */
	__u32 min_type;		/* in */
	__u32 max_type;		/* in */

	/*
	 * input: The maximum amount of results desired.
	 * output: The actual amount of items वापसed, restricted by any of:
	 *  - reaching the upper bound of the search range
	 *  - reaching the input nr_items amount of items
	 *  - completely filling the supplied memory buffer
	 */
	__u32 nr_items;		/* in/out */

	/* align to 64 bits */
	__u32 unused;

	/* some extra क्रम later */
	__u64 unused1;
	__u64 unused2;
	__u64 unused3;
	__u64 unused4;
पूर्ण;

काष्ठा btrfs_ioctl_search_header अणु
	__u64 transid;
	__u64 objectid;
	__u64 offset;
	__u32 type;
	__u32 len;
पूर्ण;

#घोषणा BTRFS_SEARCH_ARGS_बफ_मानE (4096 - माप(काष्ठा btrfs_ioctl_search_key))
/*
 * the buf is an array of search headers where
 * each header is followed by the actual item
 * the type field is expanded to 32 bits क्रम alignment
 */
काष्ठा btrfs_ioctl_search_args अणु
	काष्ठा btrfs_ioctl_search_key key;
	अक्षर buf[BTRFS_SEARCH_ARGS_बफ_मानE];
पूर्ण;

काष्ठा btrfs_ioctl_search_args_v2 अणु
	काष्ठा btrfs_ioctl_search_key key; /* in/out - search parameters */
	__u64 buf_size;		   /* in - size of buffer
					    * out - on EOVERFLOW: needed size
					    *       to store item */
	__u64 buf[0];                       /* out - found items */
पूर्ण;

काष्ठा btrfs_ioctl_clone_range_args अणु
  __s64 src_fd;
  __u64 src_offset, src_length;
  __u64 dest_offset;
पूर्ण;

/*
 * flags definition क्रम the defrag range ioctl
 *
 * Used by:
 * काष्ठा btrfs_ioctl_defrag_range_args.flags
 */
#घोषणा BTRFS_DEFRAG_RANGE_COMPRESS 1
#घोषणा BTRFS_DEFRAG_RANGE_START_IO 2
काष्ठा btrfs_ioctl_defrag_range_args अणु
	/* start of the defrag operation */
	__u64 start;

	/* number of bytes to defrag, use (u64)-1 to say all */
	__u64 len;

	/*
	 * flags क्रम the operation, which can include turning
	 * on compression क्रम this one defrag
	 */
	__u64 flags;

	/*
	 * any extent bigger than this will be considered
	 * alपढ़ोy defragged.  Use 0 to take the kernel शेष
	 * Use 1 to say every single extent must be rewritten
	 */
	__u32 extent_thresh;

	/*
	 * which compression method to use अगर turning on compression
	 * क्रम this defrag operation.  If unspecअगरied, zlib will
	 * be used
	 */
	__u32 compress_type;

	/* spare क्रम later */
	__u32 unused[4];
पूर्ण;


#घोषणा BTRFS_SAME_DATA_DIFFERS	1
/* For extent-same ioctl */
काष्ठा btrfs_ioctl_same_extent_info अणु
	__s64 fd;		/* in - destination file */
	__u64 logical_offset;	/* in - start of extent in destination */
	__u64 bytes_deduped;	/* out - total # of bytes we were able
				 * to dedupe from this file */
	/* status of this dedupe operation:
	 * 0 अगर dedup succeeds
	 * < 0 क्रम error
	 * == BTRFS_SAME_DATA_DIFFERS अगर data dअगरfers
	 */
	__s32 status;		/* out - see above description */
	__u32 reserved;
पूर्ण;

काष्ठा btrfs_ioctl_same_args अणु
	__u64 logical_offset;	/* in - start of extent in source */
	__u64 length;		/* in - length of extent */
	__u16 dest_count;	/* in - total elements in info array */
	__u16 reserved1;
	__u32 reserved2;
	काष्ठा btrfs_ioctl_same_extent_info info[0];
पूर्ण;

काष्ठा btrfs_ioctl_space_info अणु
	__u64 flags;
	__u64 total_bytes;
	__u64 used_bytes;
पूर्ण;

काष्ठा btrfs_ioctl_space_args अणु
	__u64 space_slots;
	__u64 total_spaces;
	काष्ठा btrfs_ioctl_space_info spaces[0];
पूर्ण;

काष्ठा btrfs_data_container अणु
	__u32	bytes_left;	/* out -- bytes not needed to deliver output */
	__u32	bytes_missing;	/* out -- additional bytes needed क्रम result */
	__u32	elem_cnt;	/* out */
	__u32	elem_missed;	/* out */
	__u64	val[0];		/* out */
पूर्ण;

काष्ठा btrfs_ioctl_ino_path_args अणु
	__u64				inum;		/* in */
	__u64				size;		/* in */
	__u64				reserved[4];
	/* काष्ठा btrfs_data_container	*fspath;	   out */
	__u64				fspath;		/* out */
पूर्ण;

काष्ठा btrfs_ioctl_logical_ino_args अणु
	__u64				logical;	/* in */
	__u64				size;		/* in */
	__u64				reserved[3];	/* must be 0 क्रम now */
	__u64				flags;		/* in, v2 only */
	/* काष्ठा btrfs_data_container	*inodes;	out   */
	__u64				inodes;
पूर्ण;
/* Return every ref to the extent, not just those containing logical block.
 * Requires logical == extent bytenr. */
#घोषणा BTRFS_LOGICAL_INO_ARGS_IGNORE_OFFSET	(1ULL << 0)

क्रमागत btrfs_dev_stat_values अणु
	/* disk I/O failure stats */
	BTRFS_DEV_STAT_WRITE_ERRS, /* EIO or EREMOTEIO from lower layers */
	BTRFS_DEV_STAT_READ_ERRS, /* EIO or EREMOTEIO from lower layers */
	BTRFS_DEV_STAT_FLUSH_ERRS, /* EIO or EREMOTEIO from lower layers */

	/* stats क्रम indirect indications क्रम I/O failures */
	BTRFS_DEV_STAT_CORRUPTION_ERRS, /* checksum error, bytenr error or
					 * contents is illegal: this is an
					 * indication that the block was damaged
					 * during पढ़ो or ग_लिखो, or written to
					 * wrong location or पढ़ो from wrong
					 * location */
	BTRFS_DEV_STAT_GENERATION_ERRS, /* an indication that blocks have not
					 * been written */

	BTRFS_DEV_STAT_VALUES_MAX
पूर्ण;

/* Reset statistics after पढ़ोing; needs SYS_ADMIN capability */
#घोषणा	BTRFS_DEV_STATS_RESET		(1ULL << 0)

काष्ठा btrfs_ioctl_get_dev_stats अणु
	__u64 devid;				/* in */
	__u64 nr_items;				/* in/out */
	__u64 flags;				/* in/out */

	/* out values: */
	__u64 values[BTRFS_DEV_STAT_VALUES_MAX];

	/*
	 * This pads the काष्ठा to 1032 bytes. It was originally meant to pad to
	 * 1024 bytes, but when adding the flags field, the padding calculation
	 * was not adjusted.
	 */
	__u64 unused[128 - 2 - BTRFS_DEV_STAT_VALUES_MAX];
पूर्ण;

#घोषणा BTRFS_QUOTA_CTL_ENABLE	1
#घोषणा BTRFS_QUOTA_CTL_DISABLE	2
#घोषणा BTRFS_QUOTA_CTL_RESCAN__NOTUSED	3
काष्ठा btrfs_ioctl_quota_ctl_args अणु
	__u64 cmd;
	__u64 status;
पूर्ण;

काष्ठा btrfs_ioctl_quota_rescan_args अणु
	__u64	flags;
	__u64   progress;
	__u64   reserved[6];
पूर्ण;

काष्ठा btrfs_ioctl_qgroup_assign_args अणु
	__u64 assign;
	__u64 src;
	__u64 dst;
पूर्ण;

काष्ठा btrfs_ioctl_qgroup_create_args अणु
	__u64 create;
	__u64 qgroupid;
पूर्ण;
काष्ठा btrfs_ioctl_बारpec अणु
	__u64 sec;
	__u32 nsec;
पूर्ण;

काष्ठा btrfs_ioctl_received_subvol_args अणु
	अक्षर	uuid[BTRFS_UUID_SIZE];	/* in */
	__u64	stransid;		/* in */
	__u64	rtransid;		/* out */
	काष्ठा btrfs_ioctl_बारpec sसमय; /* in */
	काष्ठा btrfs_ioctl_बारpec rसमय; /* out */
	__u64	flags;			/* in */
	__u64	reserved[16];		/* in */
पूर्ण;

/*
 * Caller करोesn't want file data in the send stream, even अगर the
 * search of clone sources करोesn't find an extent. UPDATE_EXTENT
 * commands will be sent instead of WRITE commands.
 */
#घोषणा BTRFS_SEND_FLAG_NO_खाता_DATA		0x1

/*
 * Do not add the leading stream header. Used when multiple snapshots
 * are sent back to back.
 */
#घोषणा BTRFS_SEND_FLAG_OMIT_STREAM_HEADER	0x2

/*
 * Omit the command at the end of the stream that indicated the end
 * of the stream. This option is used when multiple snapshots are
 * sent back to back.
 */
#घोषणा BTRFS_SEND_FLAG_OMIT_END_CMD		0x4

#घोषणा BTRFS_SEND_FLAG_MASK \
	(BTRFS_SEND_FLAG_NO_खाता_DATA | \
	 BTRFS_SEND_FLAG_OMIT_STREAM_HEADER | \
	 BTRFS_SEND_FLAG_OMIT_END_CMD)

काष्ठा btrfs_ioctl_send_args अणु
	__s64 send_fd;			/* in */
	__u64 clone_sources_count;	/* in */
	__u64 __user *clone_sources;	/* in */
	__u64 parent_root;		/* in */
	__u64 flags;			/* in */
	__u64 reserved[4];		/* in */
पूर्ण;

/*
 * Inक्रमmation about a fs tree root.
 *
 * All items are filled by the ioctl
 */
काष्ठा btrfs_ioctl_get_subvol_info_args अणु
	/* Id of this subvolume */
	__u64 treeid;

	/* Name of this subvolume, used to get the real name at mount poपूर्णांक */
	अक्षर name[BTRFS_VOL_NAME_MAX + 1];

	/*
	 * Id of the subvolume which contains this subvolume.
	 * Zero क्रम top-level subvolume or a deleted subvolume.
	 */
	__u64 parent_id;

	/*
	 * Inode number of the directory which contains this subvolume.
	 * Zero क्रम top-level subvolume or a deleted subvolume
	 */
	__u64 dirid;

	/* Latest transaction id of this subvolume */
	__u64 generation;

	/* Flags of this subvolume */
	__u64 flags;

	/* UUID of this subvolume */
	__u8 uuid[BTRFS_UUID_SIZE];

	/*
	 * UUID of the subvolume of which this subvolume is a snapshot.
	 * All zero क्रम a non-snapshot subvolume.
	 */
	__u8 parent_uuid[BTRFS_UUID_SIZE];

	/*
	 * UUID of the subvolume from which this subvolume was received.
	 * All zero क्रम non-received subvolume.
	 */
	__u8 received_uuid[BTRFS_UUID_SIZE];

	/* Transaction id indicating when change/create/send/receive happened */
	__u64 ctransid;
	__u64 otransid;
	__u64 stransid;
	__u64 rtransid;
	/* Time corresponding to c/o/s/rtransid */
	काष्ठा btrfs_ioctl_बारpec स_समय;
	काष्ठा btrfs_ioctl_बारpec oसमय;
	काष्ठा btrfs_ioctl_बारpec sसमय;
	काष्ठा btrfs_ioctl_बारpec rसमय;

	/* Must be zero */
	__u64 reserved[8];
पूर्ण;

#घोषणा BTRFS_MAX_ROOTREF_BUFFER_NUM 255
काष्ठा btrfs_ioctl_get_subvol_rootref_args अणु
		/* in/out, minimum id of rootref's treeid to be searched */
		__u64 min_treeid;

		/* out */
		काष्ठा अणु
			__u64 treeid;
			__u64 dirid;
		पूर्ण rootref[BTRFS_MAX_ROOTREF_BUFFER_NUM];

		/* out, number of found items */
		__u8 num_items;
		__u8 align[7];
पूर्ण;

/* Error codes as वापसed by the kernel */
क्रमागत btrfs_err_code अणु
	BTRFS_ERROR_DEV_RAID1_MIN_NOT_MET = 1,
	BTRFS_ERROR_DEV_RAID10_MIN_NOT_MET,
	BTRFS_ERROR_DEV_RAID5_MIN_NOT_MET,
	BTRFS_ERROR_DEV_RAID6_MIN_NOT_MET,
	BTRFS_ERROR_DEV_TGT_REPLACE,
	BTRFS_ERROR_DEV_MISSING_NOT_FOUND,
	BTRFS_ERROR_DEV_ONLY_WRITABLE,
	BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS,
	BTRFS_ERROR_DEV_RAID1C3_MIN_NOT_MET,
	BTRFS_ERROR_DEV_RAID1C4_MIN_NOT_MET,
पूर्ण;

#घोषणा BTRFS_IOC_SNAP_CREATE _IOW(BTRFS_IOCTL_MAGIC, 1, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_DEFRAG _IOW(BTRFS_IOCTL_MAGIC, 2, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_RESIZE _IOW(BTRFS_IOCTL_MAGIC, 3, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_SCAN_DEV _IOW(BTRFS_IOCTL_MAGIC, 4, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_FORGET_DEV _IOW(BTRFS_IOCTL_MAGIC, 5, \
				   काष्ठा btrfs_ioctl_vol_args)
/* trans start and trans end are dangerous, and only क्रम
 * use by applications that know how to aव्योम the
 * resulting deadlocks
 */
#घोषणा BTRFS_IOC_TRANS_START  _IO(BTRFS_IOCTL_MAGIC, 6)
#घोषणा BTRFS_IOC_TRANS_END    _IO(BTRFS_IOCTL_MAGIC, 7)
#घोषणा BTRFS_IOC_SYNC         _IO(BTRFS_IOCTL_MAGIC, 8)

#घोषणा BTRFS_IOC_CLONE        _IOW(BTRFS_IOCTL_MAGIC, 9, पूर्णांक)
#घोषणा BTRFS_IOC_ADD_DEV _IOW(BTRFS_IOCTL_MAGIC, 10, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_RM_DEV _IOW(BTRFS_IOCTL_MAGIC, 11, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_BALANCE _IOW(BTRFS_IOCTL_MAGIC, 12, \
				   काष्ठा btrfs_ioctl_vol_args)

#घोषणा BTRFS_IOC_CLONE_RANGE _IOW(BTRFS_IOCTL_MAGIC, 13, \
				  काष्ठा btrfs_ioctl_clone_range_args)

#घोषणा BTRFS_IOC_SUBVOL_CREATE _IOW(BTRFS_IOCTL_MAGIC, 14, \
				   काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_SNAP_DESTROY _IOW(BTRFS_IOCTL_MAGIC, 15, \
				काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_DEFRAG_RANGE _IOW(BTRFS_IOCTL_MAGIC, 16, \
				काष्ठा btrfs_ioctl_defrag_range_args)
#घोषणा BTRFS_IOC_TREE_SEARCH _IOWR(BTRFS_IOCTL_MAGIC, 17, \
				   काष्ठा btrfs_ioctl_search_args)
#घोषणा BTRFS_IOC_TREE_SEARCH_V2 _IOWR(BTRFS_IOCTL_MAGIC, 17, \
					   काष्ठा btrfs_ioctl_search_args_v2)
#घोषणा BTRFS_IOC_INO_LOOKUP _IOWR(BTRFS_IOCTL_MAGIC, 18, \
				   काष्ठा btrfs_ioctl_ino_lookup_args)
#घोषणा BTRFS_IOC_DEFAULT_SUBVOL _IOW(BTRFS_IOCTL_MAGIC, 19, __u64)
#घोषणा BTRFS_IOC_SPACE_INFO _IOWR(BTRFS_IOCTL_MAGIC, 20, \
				    काष्ठा btrfs_ioctl_space_args)
#घोषणा BTRFS_IOC_START_SYNC _IOR(BTRFS_IOCTL_MAGIC, 24, __u64)
#घोषणा BTRFS_IOC_WAIT_SYNC  _IOW(BTRFS_IOCTL_MAGIC, 22, __u64)
#घोषणा BTRFS_IOC_SNAP_CREATE_V2 _IOW(BTRFS_IOCTL_MAGIC, 23, \
				   काष्ठा btrfs_ioctl_vol_args_v2)
#घोषणा BTRFS_IOC_SUBVOL_CREATE_V2 _IOW(BTRFS_IOCTL_MAGIC, 24, \
				   काष्ठा btrfs_ioctl_vol_args_v2)
#घोषणा BTRFS_IOC_SUBVOL_GETFLAGS _IOR(BTRFS_IOCTL_MAGIC, 25, __u64)
#घोषणा BTRFS_IOC_SUBVOL_SETFLAGS _IOW(BTRFS_IOCTL_MAGIC, 26, __u64)
#घोषणा BTRFS_IOC_SCRUB _IOWR(BTRFS_IOCTL_MAGIC, 27, \
			      काष्ठा btrfs_ioctl_scrub_args)
#घोषणा BTRFS_IOC_SCRUB_CANCEL _IO(BTRFS_IOCTL_MAGIC, 28)
#घोषणा BTRFS_IOC_SCRUB_PROGRESS _IOWR(BTRFS_IOCTL_MAGIC, 29, \
				       काष्ठा btrfs_ioctl_scrub_args)
#घोषणा BTRFS_IOC_DEV_INFO _IOWR(BTRFS_IOCTL_MAGIC, 30, \
				 काष्ठा btrfs_ioctl_dev_info_args)
#घोषणा BTRFS_IOC_FS_INFO _IOR(BTRFS_IOCTL_MAGIC, 31, \
			       काष्ठा btrfs_ioctl_fs_info_args)
#घोषणा BTRFS_IOC_BALANCE_V2 _IOWR(BTRFS_IOCTL_MAGIC, 32, \
				   काष्ठा btrfs_ioctl_balance_args)
#घोषणा BTRFS_IOC_BALANCE_CTL _IOW(BTRFS_IOCTL_MAGIC, 33, पूर्णांक)
#घोषणा BTRFS_IOC_BALANCE_PROGRESS _IOR(BTRFS_IOCTL_MAGIC, 34, \
					काष्ठा btrfs_ioctl_balance_args)
#घोषणा BTRFS_IOC_INO_PATHS _IOWR(BTRFS_IOCTL_MAGIC, 35, \
					काष्ठा btrfs_ioctl_ino_path_args)
#घोषणा BTRFS_IOC_LOGICAL_INO _IOWR(BTRFS_IOCTL_MAGIC, 36, \
					काष्ठा btrfs_ioctl_logical_ino_args)
#घोषणा BTRFS_IOC_SET_RECEIVED_SUBVOL _IOWR(BTRFS_IOCTL_MAGIC, 37, \
				काष्ठा btrfs_ioctl_received_subvol_args)
#घोषणा BTRFS_IOC_SEND _IOW(BTRFS_IOCTL_MAGIC, 38, काष्ठा btrfs_ioctl_send_args)
#घोषणा BTRFS_IOC_DEVICES_READY _IOR(BTRFS_IOCTL_MAGIC, 39, \
				     काष्ठा btrfs_ioctl_vol_args)
#घोषणा BTRFS_IOC_QUOTA_CTL _IOWR(BTRFS_IOCTL_MAGIC, 40, \
			       काष्ठा btrfs_ioctl_quota_ctl_args)
#घोषणा BTRFS_IOC_QGROUP_ASSIGN _IOW(BTRFS_IOCTL_MAGIC, 41, \
			       काष्ठा btrfs_ioctl_qgroup_assign_args)
#घोषणा BTRFS_IOC_QGROUP_CREATE _IOW(BTRFS_IOCTL_MAGIC, 42, \
			       काष्ठा btrfs_ioctl_qgroup_create_args)
#घोषणा BTRFS_IOC_QGROUP_LIMIT _IOR(BTRFS_IOCTL_MAGIC, 43, \
			       काष्ठा btrfs_ioctl_qgroup_limit_args)
#घोषणा BTRFS_IOC_QUOTA_RESCAN _IOW(BTRFS_IOCTL_MAGIC, 44, \
			       काष्ठा btrfs_ioctl_quota_rescan_args)
#घोषणा BTRFS_IOC_QUOTA_RESCAN_STATUS _IOR(BTRFS_IOCTL_MAGIC, 45, \
			       काष्ठा btrfs_ioctl_quota_rescan_args)
#घोषणा BTRFS_IOC_QUOTA_RESCAN_WAIT _IO(BTRFS_IOCTL_MAGIC, 46)
#घोषणा BTRFS_IOC_GET_FSLABEL 	FS_IOC_GETFSLABEL
#घोषणा BTRFS_IOC_SET_FSLABEL	FS_IOC_SETFSLABEL
#घोषणा BTRFS_IOC_GET_DEV_STATS _IOWR(BTRFS_IOCTL_MAGIC, 52, \
				      काष्ठा btrfs_ioctl_get_dev_stats)
#घोषणा BTRFS_IOC_DEV_REPLACE _IOWR(BTRFS_IOCTL_MAGIC, 53, \
				    काष्ठा btrfs_ioctl_dev_replace_args)
#घोषणा BTRFS_IOC_खाता_EXTENT_SAME _IOWR(BTRFS_IOCTL_MAGIC, 54, \
					 काष्ठा btrfs_ioctl_same_args)
#घोषणा BTRFS_IOC_GET_FEATURES _IOR(BTRFS_IOCTL_MAGIC, 57, \
				   काष्ठा btrfs_ioctl_feature_flags)
#घोषणा BTRFS_IOC_SET_FEATURES _IOW(BTRFS_IOCTL_MAGIC, 57, \
				   काष्ठा btrfs_ioctl_feature_flags[2])
#घोषणा BTRFS_IOC_GET_SUPPORTED_FEATURES _IOR(BTRFS_IOCTL_MAGIC, 57, \
				   काष्ठा btrfs_ioctl_feature_flags[3])
#घोषणा BTRFS_IOC_RM_DEV_V2 _IOW(BTRFS_IOCTL_MAGIC, 58, \
				   काष्ठा btrfs_ioctl_vol_args_v2)
#घोषणा BTRFS_IOC_LOGICAL_INO_V2 _IOWR(BTRFS_IOCTL_MAGIC, 59, \
					काष्ठा btrfs_ioctl_logical_ino_args)
#घोषणा BTRFS_IOC_GET_SUBVOL_INFO _IOR(BTRFS_IOCTL_MAGIC, 60, \
				काष्ठा btrfs_ioctl_get_subvol_info_args)
#घोषणा BTRFS_IOC_GET_SUBVOL_ROOTREF _IOWR(BTRFS_IOCTL_MAGIC, 61, \
				काष्ठा btrfs_ioctl_get_subvol_rootref_args)
#घोषणा BTRFS_IOC_INO_LOOKUP_USER _IOWR(BTRFS_IOCTL_MAGIC, 62, \
				काष्ठा btrfs_ioctl_ino_lookup_user_args)
#घोषणा BTRFS_IOC_SNAP_DESTROY_V2 _IOW(BTRFS_IOCTL_MAGIC, 63, \
				काष्ठा btrfs_ioctl_vol_args_v2)

#पूर्ण_अगर /* _UAPI_LINUX_BTRFS_H */
