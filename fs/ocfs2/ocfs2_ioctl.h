<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ocfs2_ioctl.h
 *
 * Defines OCFS2 ioctls.
 *
 * Copyright (C) 2010 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_IOCTL_H
#घोषणा OCFS2_IOCTL_H

/*
 * Space reservation / allocation / मुक्त ioctls and argument काष्ठाure
 * are deचिन्हित to be compatible with XFS.
 *
 * ALLOCSP* and FREESP* are not and will never be supported, but are
 * included here क्रम completeness.
 */
काष्ठा ocfs2_space_resv अणु
	__s16		l_type;
	__s16		l_whence;
	__s64		l_start;
	__s64		l_len;		/* len == 0 means until end of file */
	__s32		l_sysid;
	__u32		l_pid;
	__s32		l_pad[4];	/* reserve area			    */
पूर्ण;

#घोषणा OCFS2_IOC_ALLOCSP		_IOW ('X', 10, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_FREESP		_IOW ('X', 11, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_RESVSP		_IOW ('X', 40, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_UNRESVSP	_IOW ('X', 41, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_ALLOCSP64	_IOW ('X', 36, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_FREESP64	_IOW ('X', 37, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_RESVSP64	_IOW ('X', 42, काष्ठा ocfs2_space_resv)
#घोषणा OCFS2_IOC_UNRESVSP64	_IOW ('X', 43, काष्ठा ocfs2_space_resv)

/* Used to pass group descriptor data when online resize is करोne */
काष्ठा ocfs2_new_group_input अणु
	__u64 group;		/* Group descriptor's blkno. */
	__u32 clusters;		/* Total number of clusters in this group */
	__u32 मुक्तs;		/* Total मुक्त clusters in this group */
	__u16 chain;		/* Chain क्रम this group */
	__u16 reserved1;
	__u32 reserved2;
पूर्ण;

#घोषणा OCFS2_IOC_GROUP_EXTEND	_IOW('o', 1, पूर्णांक)
#घोषणा OCFS2_IOC_GROUP_ADD	_IOW('o', 2,काष्ठा ocfs2_new_group_input)
#घोषणा OCFS2_IOC_GROUP_ADD64	_IOW('o', 3,काष्ठा ocfs2_new_group_input)

/* Used to pass 2 file names to reflink. */
काष्ठा reflink_arguments अणु
	__u64 old_path;
	__u64 new_path;
	__u64 preserve;
पूर्ण;
#घोषणा OCFS2_IOC_REFLINK	_IOW('o', 4, काष्ठा reflink_arguments)

/* Following definitions dedicated क्रम ocfs2_info_request ioctls. */
#घोषणा OCFS2_INFO_MAX_REQUEST		(50)
#घोषणा OCFS2_TEXT_UUID_LEN		(OCFS2_VOL_UUID_LEN * 2)

/* Magic number of all requests */
#घोषणा OCFS2_INFO_MAGIC		(0x4F32494E)

/*
 * Always try to separate info request पूर्णांकo small pieces to
 * guarantee the backward&क्रमward compatibility.
 */
काष्ठा ocfs2_info अणु
	__u64 oi_requests;	/* Array of __u64 poपूर्णांकers to requests */
	__u32 oi_count;		/* Number of requests in info_requests */
	__u32 oi_pad;
पूर्ण;

काष्ठा ocfs2_info_request अणु
/*00*/	__u32 ir_magic;	/* Magic number */
	__u32 ir_code;	/* Info request code */
	__u32 ir_size;	/* Size of request */
	__u32 ir_flags;	/* Request flags */
/*10*/			/* Request specअगरic fields */
पूर्ण;

काष्ठा ocfs2_info_clustersize अणु
	काष्ठा ocfs2_info_request ic_req;
	__u32 ic_clustersize;
	__u32 ic_pad;
पूर्ण;

काष्ठा ocfs2_info_blocksize अणु
	काष्ठा ocfs2_info_request ib_req;
	__u32 ib_blocksize;
	__u32 ib_pad;
पूर्ण;

काष्ठा ocfs2_info_maxslots अणु
	काष्ठा ocfs2_info_request im_req;
	__u32 im_max_slots;
	__u32 im_pad;
पूर्ण;

काष्ठा ocfs2_info_label अणु
	काष्ठा ocfs2_info_request il_req;
	__u8	il_label[OCFS2_MAX_VOL_LABEL_LEN];
पूर्ण __attribute__ ((packed));

काष्ठा ocfs2_info_uuid अणु
	काष्ठा ocfs2_info_request iu_req;
	__u8	iu_uuid_str[OCFS2_TEXT_UUID_LEN + 1];
पूर्ण __attribute__ ((packed));

काष्ठा ocfs2_info_fs_features अणु
	काष्ठा ocfs2_info_request अगर_req;
	__u32 अगर_compat_features;
	__u32 अगर_incompat_features;
	__u32 अगर_ro_compat_features;
	__u32 अगर_pad;
पूर्ण;

काष्ठा ocfs2_info_journal_size अणु
	काष्ठा ocfs2_info_request ij_req;
	__u64 ij_journal_size;
पूर्ण;

काष्ठा ocfs2_info_मुक्तinode अणु
	काष्ठा ocfs2_info_request अगरi_req;
	काष्ठा ocfs2_info_local_मुक्तinode अणु
		__u64 lfi_total;
		__u64 lfi_मुक्त;
	पूर्ण अगरi_stat[OCFS2_MAX_SLOTS];
	__u32 अगरi_slotnum; /* out */
	__u32 अगरi_pad;
पूर्ण;

#घोषणा OCFS2_INFO_MAX_HIST     (32)

काष्ठा ocfs2_info_मुक्तfrag अणु
	काष्ठा ocfs2_info_request अगरf_req;
	काष्ठा ocfs2_info_मुक्तfrag_stats अणु /* (out) */
		काष्ठा ocfs2_info_मुक्त_chunk_list अणु
			__u32 fc_chunks[OCFS2_INFO_MAX_HIST];
			__u32 fc_clusters[OCFS2_INFO_MAX_HIST];
		पूर्ण ffs_fc_hist;
		__u32 ffs_clusters;
		__u32 ffs_मुक्त_clusters;
		__u32 ffs_मुक्त_chunks;
		__u32 ffs_मुक्त_chunks_real;
		__u32 ffs_min; /* Minimum मुक्त chunksize in clusters */
		__u32 ffs_max;
		__u32 ffs_avg;
		__u32 ffs_pad;
	पूर्ण अगरf_ffs;
	__u32 अगरf_chunksize; /* chunksize in clusters(in) */
	__u32 अगरf_pad;
पूर्ण;

/* Codes क्रम ocfs2_info_request */
क्रमागत ocfs2_info_type अणु
	OCFS2_INFO_CLUSTERSIZE = 1,
	OCFS2_INFO_BLOCKSIZE,
	OCFS2_INFO_MAXSLOTS,
	OCFS2_INFO_LABEL,
	OCFS2_INFO_UUID,
	OCFS2_INFO_FS_FEATURES,
	OCFS2_INFO_JOURNAL_SIZE,
	OCFS2_INFO_FREEINODE,
	OCFS2_INFO_FREEFRAG,
	OCFS2_INFO_NUM_TYPES
पूर्ण;

/* Flags क्रम काष्ठा ocfs2_info_request */
/* Filled by the caller */
#घोषणा OCFS2_INFO_FL_NON_COHERENT	(0x00000001)	/* Cluster coherency not
							   required. This is a hपूर्णांक.
							   It is up to ocfs2 whether
							   the request can be fulfilled
							   without locking. */
/* Filled by ocfs2 */
#घोषणा OCFS2_INFO_FL_FILLED		(0x40000000)	/* Fileप्रणाली understood
							   this request and
							   filled in the answer */

#घोषणा OCFS2_INFO_FL_ERROR		(0x80000000)	/* Error happened during
							   request handling. */

#घोषणा OCFS2_IOC_INFO		_IOR('o', 5, काष्ठा ocfs2_info)

काष्ठा ocfs2_move_extents अणु
/* All values are in bytes */
	/* in */
	__u64 me_start;		/* Virtual start in the file to move */
	__u64 me_len;		/* Length of the extents to be moved */
	__u64 me_goal;		/* Physical offset of the goal,
				   it's in block unit */
	__u64 me_threshold;	/* Maximum distance from goal or threshold
				   क्रम स्वतः defragmentation */
	__u64 me_flags;		/* Flags क्रम the operation:
				 * - स्वतः defragmentation.
				 * - refcount,xattr हालs.
				 */
	/* out */
	__u64 me_moved_len;	/* Moved/defraged length */
	__u64 me_new_offset;	/* Resulting physical location */
	__u32 me_reserved[2];	/* Reserved क्रम futhure */
पूर्ण;

#घोषणा OCFS2_MOVE_EXT_FL_AUTO_DEFRAG	(0x00000001)	/* Kernel manages to
							   claim new clusters
							   as the goal place
							   क्रम extents moving */
#घोषणा OCFS2_MOVE_EXT_FL_PART_DEFRAG	(0x00000002)	/* Allow partial extent
							   moving, is to make
							   movement less likely
							   to fail, may make fs
							   even more fragmented */
#घोषणा OCFS2_MOVE_EXT_FL_COMPLETE	(0x00000004)	/* Move or defragmenation
							   completely माला_लो करोne.
							 */

#घोषणा OCFS2_IOC_MOVE_EXT	_IOW('o', 6, काष्ठा ocfs2_move_extents)

#पूर्ण_अगर /* OCFS2_IOCTL_H */
