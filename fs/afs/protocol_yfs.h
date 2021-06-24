<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* YFS protocol bits
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा YFS_FS_SERVICE	2500
#घोषणा YFS_CM_SERVICE	2501

#घोषणा YFSCBMAX	1024

क्रमागत YFS_CM_Operations अणु
	YFSCBProbe		= 206,	/* probe client */
	YFSCBGetLock		= 207,	/* get contents of CM lock table */
	YFSCBXStatsVersion	= 209,	/* get version of extended statistics */
	YFSCBGetXStats		= 210,	/* get contents of extended statistics data */
	YFSCBInitCallBackState3	= 213,	/* initialise callback state, version 3 */
	YFSCBProbeUuid		= 214,	/* check the client hasn't rebooted */
	YFSCBGetServerPrefs	= 215,
	YFSCBGetCellServDV	= 216,
	YFSCBGetLocalCell	= 217,
	YFSCBGetCacheConfig	= 218,
	YFSCBGetCellByNum	= 65537,
	YFSCBTellMeAboutYourself = 65538, /* get client capabilities */
	YFSCBCallBack		= 64204,
पूर्ण;

क्रमागत YFS_FS_Operations अणु
	YFSFETCHACL		= 64131, /* YFS Fetch file AFS3 ACL */
	YFSFETCHSTATUS		= 64132, /* YFS Fetch file status */
	YFSSTOREACL		= 64134, /* YFS Store file AFS3 ACL */
	YFSSTORESTATUS		= 64135, /* YFS Store file status */
	YFSREMOVEखाता		= 64136, /* YFS Remove a file */
	YFSCREATEखाता		= 64137, /* YFS Create a file */
	YFSRENAME		= 64138, /* YFS Rename or move a file or directory */
	YFSSYMLINK		= 64139, /* YFS Create a symbolic link */
	YFSLINK			= 64140, /* YFS Create a hard link */
	YFSMAKEसूची		= 64141, /* YFS Create a directory */
	YFSREMOVEसूची		= 64142, /* YFS Remove a directory */
	YFSGETVOLUMESTATUS	= 64149, /* YFS Get volume status inक्रमmation */
	YFSSETVOLUMESTATUS	= 64150, /* YFS Set volume status inक्रमmation */
	YFSSETLOCK		= 64156, /* YFS Request a file lock */
	YFSEXTENDLOCK		= 64157, /* YFS Extend a file lock */
	YFSRELEASELOCK		= 64158, /* YFS Release a file lock */
	YFSLOOKUP		= 64161, /* YFS lookup file in directory */
	YFSFLUSHCPS		= 64165,
	YFSFETCHOPAQUEACL	= 64168, /* YFS Fetch file YFS ACL */
	YFSWHOAMI		= 64170,
	YFSREMOVEACL		= 64171,
	YFSREMOVEखाता2		= 64173,
	YFSSTOREOPAQUEACL2	= 64174,
	YFSINLINEBULKSTATUS	= 64536, /* YFS Fetch multiple file statuses with errors */
	YFSFETCHDATA64		= 64537, /* YFS Fetch file data */
	YFSSTOREDATA64		= 64538, /* YFS Store file data */
	YFSUPDATESYMLINK	= 64540,
पूर्ण;

काष्ठा yfs_xdr_u64 अणु
	__be32			msw;
	__be32			lsw;
पूर्ण __packed;

अटल अंतरभूत u64 xdr_to_u64(स्थिर काष्ठा yfs_xdr_u64 x)
अणु
	वापस ((u64)ntohl(x.msw) << 32) | ntohl(x.lsw);
पूर्ण

अटल अंतरभूत काष्ठा yfs_xdr_u64 u64_to_xdr(स्थिर u64 x)
अणु
	वापस (काष्ठा yfs_xdr_u64)अणु .msw = htonl(x >> 32), .lsw = htonl(x) पूर्ण;
पूर्ण

काष्ठा yfs_xdr_vnode अणु
	काष्ठा yfs_xdr_u64	lo;
	__be32			hi;
	__be32			unique;
पूर्ण __packed;

काष्ठा yfs_xdr_YFSFid अणु
	काष्ठा yfs_xdr_u64	volume;
	काष्ठा yfs_xdr_vnode	vnode;
पूर्ण __packed;


काष्ठा yfs_xdr_YFSFetchStatus अणु
	__be32			type;
	__be32			nlink;
	काष्ठा yfs_xdr_u64	size;
	काष्ठा yfs_xdr_u64	data_version;
	काष्ठा yfs_xdr_u64	author;
	काष्ठा yfs_xdr_u64	owner;
	काष्ठा yfs_xdr_u64	group;
	__be32			mode;
	__be32			caller_access;
	__be32			anon_access;
	काष्ठा yfs_xdr_vnode	parent;
	__be32			data_access_protocol;
	काष्ठा yfs_xdr_u64	mसमय_client;
	काष्ठा yfs_xdr_u64	mसमय_server;
	__be32			lock_count;
	__be32			पात_code;
पूर्ण __packed;

काष्ठा yfs_xdr_YFSCallBack अणु
	__be32			version;
	काष्ठा yfs_xdr_u64	expiration_समय;
	__be32			type;
पूर्ण __packed;

काष्ठा yfs_xdr_YFSStoreStatus अणु
	__be32			mask;
	__be32			mode;
	काष्ठा yfs_xdr_u64	mसमय_client;
	काष्ठा yfs_xdr_u64	owner;
	काष्ठा yfs_xdr_u64	group;
पूर्ण __packed;

काष्ठा yfs_xdr_RPCFlags अणु
	__be32			rpc_flags;
पूर्ण __packed;

काष्ठा yfs_xdr_YFSVolSync अणु
	काष्ठा yfs_xdr_u64	vol_creation_date;
	काष्ठा yfs_xdr_u64	vol_update_date;
	काष्ठा yfs_xdr_u64	max_quota;
	काष्ठा yfs_xdr_u64	blocks_in_use;
	काष्ठा yfs_xdr_u64	blocks_avail;
पूर्ण __packed;

क्रमागत yfs_volume_type अणु
	yfs_volume_type_ro = 0,
	yfs_volume_type_rw = 1,
पूर्ण;

#घोषणा yfs_FVSOnline		0x1
#घोषणा yfs_FVSInservice	0x2
#घोषणा yfs_FVSBlessed		0x4
#घोषणा yfs_FVSNeedsSalvage	0x8

काष्ठा yfs_xdr_YFSFetchVolumeStatus अणु
	काष्ठा yfs_xdr_u64	vid;
	काष्ठा yfs_xdr_u64	parent_id;
	__be32			flags;
	__be32			type;
	काष्ठा yfs_xdr_u64	max_quota;
	काष्ठा yfs_xdr_u64	blocks_in_use;
	काष्ठा yfs_xdr_u64	part_blocks_avail;
	काष्ठा yfs_xdr_u64	part_max_blocks;
	काष्ठा yfs_xdr_u64	vol_copy_date;
	काष्ठा yfs_xdr_u64	vol_backup_date;
पूर्ण __packed;

काष्ठा yfs_xdr_YFSStoreVolumeStatus अणु
	__be32			mask;
	काष्ठा yfs_xdr_u64	min_quota;
	काष्ठा yfs_xdr_u64	max_quota;
	काष्ठा yfs_xdr_u64	file_quota;
पूर्ण __packed;

क्रमागत yfs_lock_type अणु
	yfs_LockNone		= -1,
	yfs_LockRead		= 0,
	yfs_LockWrite		= 1,
	yfs_LockExtend		= 2,
	yfs_LockRelease		= 3,
	yfs_LockMandatoryRead	= 0x100,
	yfs_LockMandatoryWrite	= 0x101,
	yfs_LockMandatoryExtend	= 0x102,
पूर्ण;
