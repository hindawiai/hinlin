<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* AFS common types
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#अगर_अघोषित AFS_H
#घोषणा AFS_H

#समावेश <linux/in.h>

#घोषणा AFS_MAXCELLNAME		256  	/* Maximum length of a cell name */
#घोषणा AFS_MAXVOLNAME		64  	/* Maximum length of a volume name */
#घोषणा AFS_MAXNSERVERS		8   	/* Maximum servers in a basic volume record */
#घोषणा AFS_NMAXNSERVERS	13  	/* Maximum servers in a N/U-class volume record */
#घोषणा AFS_MAXTYPES		3	/* Maximum number of volume types */
#घोषणा AFSNAMEMAX		256 	/* Maximum length of a filename plus NUL */
#घोषणा AFSPATHMAX		1024	/* Maximum length of a pathname plus NUL */
#घोषणा AFSOPAQUEMAX		1024	/* Maximum length of an opaque field */

#घोषणा AFS_VL_MAX_LIFESPAN	(120 * HZ)
#घोषणा AFS_PROBE_MAX_LIFESPAN	(30 * HZ)

प्रकार u64			afs_volid_t;
प्रकार u64			afs_vnodeid_t;
प्रकार u64			afs_dataversion_t;

प्रकार क्रमागत अणु
	AFSVL_RWVOL,			/* पढ़ो/ग_लिखो volume */
	AFSVL_ROVOL,			/* पढ़ो-only volume */
	AFSVL_BACKVOL,			/* backup volume */
पूर्ण __attribute__((packed)) afs_voltype_t;

प्रकार क्रमागत अणु
	AFS_FTYPE_INVALID	= 0,
	AFS_FTYPE_खाता		= 1,
	AFS_FTYPE_सूची		= 2,
	AFS_FTYPE_SYMLINK	= 3,
पूर्ण afs_file_type_t;

प्रकार क्रमागत अणु
	AFS_LOCK_READ		= 0,	/* पढ़ो lock request */
	AFS_LOCK_WRITE		= 1,	/* ग_लिखो lock request */
पूर्ण afs_lock_type_t;

#घोषणा AFS_LOCKWAIT		(5 * 60) /* समय until a lock बार out (seconds) */

/*
 * AFS file identअगरier
 */
काष्ठा afs_fid अणु
	afs_volid_t	vid;		/* volume ID */
	afs_vnodeid_t	vnode;		/* Lower 64-bits of file index within volume */
	u32		vnode_hi;	/* Upper 32-bits of file index */
	u32		unique;		/* unique ID number (file index version) */
पूर्ण;

/*
 * AFS callback notअगरication
 */
प्रकार क्रमागत अणु
	AFSCM_CB_UNTYPED	= 0,	/* no type set on CB अवरोध */
	AFSCM_CB_EXCLUSIVE	= 1,	/* CB exclusive to CM [not implemented] */
	AFSCM_CB_SHARED		= 2,	/* CB shared by other CM's */
	AFSCM_CB_DROPPED	= 3,	/* CB promise cancelled by file server */
पूर्ण afs_callback_type_t;

काष्ठा afs_callback अणु
	समय64_t		expires_at;	/* Time at which expires */
	//अचिन्हित		version;	/* Callback version */
	//afs_callback_type_t	type;		/* Type of callback */
पूर्ण;

काष्ठा afs_callback_अवरोध अणु
	काष्ठा afs_fid		fid;		/* File identअगरier */
	//काष्ठा afs_callback	cb;		/* Callback details */
पूर्ण;

#घोषणा AFSCBMAX 50	/* maximum callbacks transferred per bulk op */

काष्ठा afs_uuid अणु
	__be32		समय_low;			/* low part of बारtamp */
	__be16		समय_mid;			/* mid part of बारtamp */
	__be16		समय_hi_and_version;		/* high part of बारtamp and version  */
	__s8		घड़ी_seq_hi_and_reserved;	/* घड़ी seq hi and variant */
	__s8		घड़ी_seq_low;			/* घड़ी seq low */
	__s8		node[6];			/* spatially unique node ID (MAC addr) */
पूर्ण;

/*
 * AFS volume inक्रमmation
 */
काष्ठा afs_volume_info अणु
	afs_volid_t		vid;		/* volume ID */
	afs_voltype_t		type;		/* type of this volume */
	afs_volid_t		type_vids[5];	/* volume ID's क्रम possible types क्रम this vol */

	/* list of fileservers serving this volume */
	माप_प्रकार			nservers;	/* number of entries used in servers[] */
	काष्ठा अणु
		काष्ठा in_addr	addr;		/* fileserver address */
	पूर्ण servers[8];
पूर्ण;

/*
 * AFS security ACE access mask
 */
प्रकार u32 afs_access_t;
#घोषणा AFS_ACE_READ		0x00000001U	/* - permission to पढ़ो a file/dir */
#घोषणा AFS_ACE_WRITE		0x00000002U	/* - permission to ग_लिखो/chmod a file */
#घोषणा AFS_ACE_INSERT		0x00000004U	/* - permission to create dirent in a dir */
#घोषणा AFS_ACE_LOOKUP		0x00000008U	/* - permission to lookup a file/dir in a dir */
#घोषणा AFS_ACE_DELETE		0x00000010U	/* - permission to delete a dirent from a dir */
#घोषणा AFS_ACE_LOCK		0x00000020U	/* - permission to lock a file */
#घोषणा AFS_ACE_ADMINISTER	0x00000040U	/* - permission to change ACL */
#घोषणा AFS_ACE_USER_A		0x01000000U	/* - 'A' user-defined permission */
#घोषणा AFS_ACE_USER_B		0x02000000U	/* - 'B' user-defined permission */
#घोषणा AFS_ACE_USER_C		0x04000000U	/* - 'C' user-defined permission */
#घोषणा AFS_ACE_USER_D		0x08000000U	/* - 'D' user-defined permission */
#घोषणा AFS_ACE_USER_E		0x10000000U	/* - 'E' user-defined permission */
#घोषणा AFS_ACE_USER_F		0x20000000U	/* - 'F' user-defined permission */
#घोषणा AFS_ACE_USER_G		0x40000000U	/* - 'G' user-defined permission */
#घोषणा AFS_ACE_USER_H		0x80000000U	/* - 'H' user-defined permission */

/*
 * AFS file status inक्रमmation
 */
काष्ठा afs_file_status अणु
	u64			size;		/* file size */
	afs_dataversion_t	data_version;	/* current data version */
	काष्ठा बारpec64	mसमय_client;	/* Last समय client changed data */
	काष्ठा बारpec64	mसमय_server;	/* Last समय server changed data */
	s64			author;		/* author ID */
	s64			owner;		/* owner ID */
	s64			group;		/* group ID */
	afs_access_t		caller_access;	/* access rights क्रम authenticated caller */
	afs_access_t		anon_access;	/* access rights क्रम unauthenticated caller */
	umode_t			mode;		/* UNIX mode */
	afs_file_type_t		type;		/* file type */
	u32			nlink;		/* link count */
	s32			lock_count;	/* file lock count (0=UNLK -1=WRLCK +ve=#RDLCK */
	u32			पात_code;	/* Abort अगर bulk-fetching this failed */
पूर्ण;

काष्ठा afs_status_cb अणु
	काष्ठा afs_file_status	status;
	काष्ठा afs_callback	callback;
	bool			have_status;	/* True अगर status record was retrieved */
	bool			have_cb;	/* True अगर cb record was retrieved */
	bool			have_error;	/* True अगर status.पात_code indicates an error */
पूर्ण;

/*
 * AFS file status change request
 */

#घोषणा AFS_SET_MTIME		0x01		/* set the mसमय */
#घोषणा AFS_SET_OWNER		0x02		/* set the owner ID */
#घोषणा AFS_SET_GROUP		0x04		/* set the group ID (unsupported?) */
#घोषणा AFS_SET_MODE		0x08		/* set the UNIX mode */
#घोषणा AFS_SET_SEG_SIZE	0x10		/* set the segment size (unsupported) */

/*
 * AFS volume synchronisation inक्रमmation
 */
काष्ठा afs_volsync अणु
	समय64_t		creation;	/* volume creation समय */
पूर्ण;

/*
 * AFS volume status record
 */
काष्ठा afs_volume_status अणु
	afs_volid_t		vid;		/* volume ID */
	afs_volid_t		parent_id;	/* parent volume ID */
	u8			online;		/* true अगर volume currently online and available */
	u8			in_service;	/* true अगर volume currently in service */
	u8			blessed;	/* same as in_service */
	u8			needs_salvage;	/* true अगर consistency checking required */
	u32			type;		/* volume type (afs_voltype_t) */
	u64			min_quota;	/* minimum space set aside (blocks) */
	u64			max_quota;	/* maximum space this volume may occupy (blocks) */
	u64			blocks_in_use;	/* space this volume currently occupies (blocks) */
	u64			part_blocks_avail; /* space available in volume's partition */
	u64			part_max_blocks; /* size of volume's partition */
	s64			vol_copy_date;
	s64			vol_backup_date;
पूर्ण;

#घोषणा AFS_BLOCK_SIZE	1024

/*
 * XDR encoding of UUID in AFS.
 */
काष्ठा afs_uuid__xdr अणु
	__be32		समय_low;
	__be32		समय_mid;
	__be32		समय_hi_and_version;
	__be32		घड़ी_seq_hi_and_reserved;
	__be32		घड़ी_seq_low;
	__be32		node[6];
पूर्ण;

#पूर्ण_अगर /* AFS_H */
