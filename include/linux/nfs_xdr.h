<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NFS_XDR_H
#घोषणा _LINUX_NFS_XDR_H

#समावेश <linux/nfsacl.h>
#समावेश <linux/sunrpc/gss_api.h>

/*
 * To change the maximum rsize and wsize supported by the NFS client, adjust
 * NFS_MAX_खाता_IO_SIZE.  64KB is a typical maximum, but some servers can
 * support a megabyte or more.  The शेष is left at 4096 bytes, which is
 * reasonable क्रम NFS over UDP.
 */
#घोषणा NFS_MAX_खाता_IO_SIZE	(1048576U)
#घोषणा NFS_DEF_खाता_IO_SIZE	(4096U)
#घोषणा NFS_MIN_खाता_IO_SIZE	(1024U)

#घोषणा NFS_BITMASK_SZ		3

काष्ठा nfs4_string अणु
	अचिन्हित पूर्णांक len;
	अक्षर *data;
पूर्ण;

काष्ठा nfs_fsid अणु
	uपूर्णांक64_t		major;
	uपूर्णांक64_t		minor;
पूर्ण;

/*
 * Helper क्रम checking equality between 2 fsids.
 */
अटल अंतरभूत पूर्णांक nfs_fsid_equal(स्थिर काष्ठा nfs_fsid *a, स्थिर काष्ठा nfs_fsid *b)
अणु
	वापस a->major == b->major && a->minor == b->minor;
पूर्ण

काष्ठा nfs4_threshold अणु
	__u32	bm;
	__u32	l_type;
	__u64	rd_sz;
	__u64	wr_sz;
	__u64	rd_io_sz;
	__u64	wr_io_sz;
पूर्ण;

काष्ठा nfs_fattr अणु
	अचिन्हित पूर्णांक		valid;		/* which fields are valid */
	umode_t			mode;
	__u32			nlink;
	kuid_t			uid;
	kgid_t			gid;
	dev_t			rdev;
	__u64			size;
	जोड़ अणु
		काष्ठा अणु
			__u32	blocksize;
			__u32	blocks;
		पूर्ण nfs2;
		काष्ठा अणु
			__u64	used;
		पूर्ण nfs3;
	पूर्ण du;
	काष्ठा nfs_fsid		fsid;
	__u64			fileid;
	__u64			mounted_on_fileid;
	काष्ठा बारpec64	aसमय;
	काष्ठा बारpec64	mसमय;
	काष्ठा बारpec64	स_समय;
	__u64			change_attr;	/* NFSv4 change attribute */
	__u64			pre_change_attr;/* pre-op NFSv4 change attribute */
	__u64			pre_size;	/* pre_op_attr.size	  */
	काष्ठा बारpec64	pre_mसमय;	/* pre_op_attr.mसमय	  */
	काष्ठा बारpec64	pre_स_समय;	/* pre_op_attr.स_समय	  */
	अचिन्हित दीर्घ		समय_start;
	अचिन्हित दीर्घ		gencount;
	काष्ठा nfs4_string	*owner_name;
	काष्ठा nfs4_string	*group_name;
	काष्ठा nfs4_threshold	*mdsthreshold;	/* pNFS threshold hपूर्णांकs */
	काष्ठा nfs4_label	*label;
पूर्ण;

#घोषणा NFS_ATTR_FATTR_TYPE		(1U << 0)
#घोषणा NFS_ATTR_FATTR_MODE		(1U << 1)
#घोषणा NFS_ATTR_FATTR_NLINK		(1U << 2)
#घोषणा NFS_ATTR_FATTR_OWNER		(1U << 3)
#घोषणा NFS_ATTR_FATTR_GROUP		(1U << 4)
#घोषणा NFS_ATTR_FATTR_RDEV		(1U << 5)
#घोषणा NFS_ATTR_FATTR_SIZE		(1U << 6)
#घोषणा NFS_ATTR_FATTR_PRESIZE		(1U << 7)
#घोषणा NFS_ATTR_FATTR_BLOCKS_USED	(1U << 8)
#घोषणा NFS_ATTR_FATTR_SPACE_USED	(1U << 9)
#घोषणा NFS_ATTR_FATTR_FSID		(1U << 10)
#घोषणा NFS_ATTR_FATTR_खाताID		(1U << 11)
#घोषणा NFS_ATTR_FATTR_ATIME		(1U << 12)
#घोषणा NFS_ATTR_FATTR_MTIME		(1U << 13)
#घोषणा NFS_ATTR_FATTR_CTIME		(1U << 14)
#घोषणा NFS_ATTR_FATTR_PREMTIME		(1U << 15)
#घोषणा NFS_ATTR_FATTR_PRECTIME		(1U << 16)
#घोषणा NFS_ATTR_FATTR_CHANGE		(1U << 17)
#घोषणा NFS_ATTR_FATTR_PRECHANGE	(1U << 18)
#घोषणा NFS_ATTR_FATTR_V4_LOCATIONS	(1U << 19)
#घोषणा NFS_ATTR_FATTR_V4_REFERRAL	(1U << 20)
#घोषणा NFS_ATTR_FATTR_MOUNTPOINT	(1U << 21)
#घोषणा NFS_ATTR_FATTR_MOUNTED_ON_खाताID (1U << 22)
#घोषणा NFS_ATTR_FATTR_OWNER_NAME	(1U << 23)
#घोषणा NFS_ATTR_FATTR_GROUP_NAME	(1U << 24)
#घोषणा NFS_ATTR_FATTR_V4_SECURITY_LABEL (1U << 25)

#घोषणा NFS_ATTR_FATTR (NFS_ATTR_FATTR_TYPE \
		| NFS_ATTR_FATTR_MODE \
		| NFS_ATTR_FATTR_NLINK \
		| NFS_ATTR_FATTR_OWNER \
		| NFS_ATTR_FATTR_GROUP \
		| NFS_ATTR_FATTR_RDEV \
		| NFS_ATTR_FATTR_SIZE \
		| NFS_ATTR_FATTR_FSID \
		| NFS_ATTR_FATTR_खाताID \
		| NFS_ATTR_FATTR_ATIME \
		| NFS_ATTR_FATTR_MTIME \
		| NFS_ATTR_FATTR_CTIME \
		| NFS_ATTR_FATTR_CHANGE)
#घोषणा NFS_ATTR_FATTR_V2 (NFS_ATTR_FATTR \
		| NFS_ATTR_FATTR_BLOCKS_USED)
#घोषणा NFS_ATTR_FATTR_V3 (NFS_ATTR_FATTR \
		| NFS_ATTR_FATTR_SPACE_USED)
#घोषणा NFS_ATTR_FATTR_V4 (NFS_ATTR_FATTR \
		| NFS_ATTR_FATTR_SPACE_USED \
		| NFS_ATTR_FATTR_V4_SECURITY_LABEL)

/*
 * Maximal number of supported layout drivers.
 */
#घोषणा NFS_MAX_LAYOUT_TYPES 8

/*
 * Info on the file प्रणाली
 */
काष्ठा nfs_fsinfo अणु
	काष्ठा nfs_fattr	*fattr; /* Post-op attributes */
	__u32			rपंचांगax;	/* max.  पढ़ो transfer size */
	__u32			rtpref;	/* pref. पढ़ो transfer size */
	__u32			rपंचांगult;	/* पढ़ोs should be multiple of this */
	__u32			wपंचांगax;	/* max.  ग_लिखो transfer size */
	__u32			wtpref;	/* pref. ग_लिखो transfer size */
	__u32			wपंचांगult;	/* ग_लिखोs should be multiple of this */
	__u32			dtpref;	/* pref. सूची_पढ़ो transfer size */
	__u64			maxfilesize;
	काष्ठा बारpec64	समय_delta; /* server समय granularity */
	__u32			lease_समय; /* in seconds */
	__u32			nlayouttypes; /* number of layouttypes */
	__u32			layouttype[NFS_MAX_LAYOUT_TYPES]; /* supported pnfs layout driver */
	__u32			blksize; /* preferred pnfs io block size */
	__u32			clone_blksize; /* granularity of a CLONE operation */
	क्रमागत nfs4_change_attr_type
				change_attr_type; /* Info about change attr */
	__u32			xattr_support; /* User xattrs supported */
पूर्ण;

काष्ठा nfs_fsstat अणु
	काष्ठा nfs_fattr	*fattr; /* Post-op attributes */
	__u64			tbytes;	/* total size in bytes */
	__u64			fbytes;	/* # of मुक्त bytes */
	__u64			abytes;	/* # of bytes available to user */
	__u64			tfiles;	/* # of files */
	__u64			ffiles;	/* # of मुक्त files */
	__u64			afiles;	/* # of files available to user */
पूर्ण;

काष्ठा nfs2_fsstat अणु
	__u32			tsize;  /* Server transfer size */
	__u32			bsize;  /* Fileप्रणाली block size */
	__u32			blocks; /* No. of "bsize" blocks on fileप्रणाली */
	__u32			bमुक्त;  /* No. of मुक्त "bsize" blocks */
	__u32			bavail; /* No. of available "bsize" blocks */
पूर्ण;

काष्ठा nfs_pathconf अणु
	काष्ठा nfs_fattr	*fattr; /* Post-op attributes */
	__u32			max_link; /* max # of hard links */
	__u32			max_namelen; /* max name length */
पूर्ण;

काष्ठा nfs4_change_info अणु
	u32			atomic;
	u64			beक्रमe;
	u64			after;
पूर्ण;

काष्ठा nfs_seqid;

/* nfs41 sessions channel attributes */
काष्ठा nfs4_channel_attrs अणु
	u32			max_rqst_sz;
	u32			max_resp_sz;
	u32			max_resp_sz_cached;
	u32			max_ops;
	u32			max_reqs;
पूर्ण;

काष्ठा nfs4_slot;
काष्ठा nfs4_sequence_args अणु
	काष्ठा nfs4_slot	*sa_slot;
	u8			sa_cache_this : 1,
				sa_privileged : 1;
पूर्ण;

काष्ठा nfs4_sequence_res अणु
	काष्ठा nfs4_slot	*sr_slot;	/* slot used to send request */
	अचिन्हित दीर्घ		sr_बारtamp;
	पूर्णांक			sr_status;	/* sequence operation status */
	u32			sr_status_flags;
	u32			sr_highest_slotid;
	u32			sr_target_highest_slotid;
पूर्ण;

काष्ठा nfs4_get_lease_समय_args अणु
	काष्ठा nfs4_sequence_args	la_seq_args;
पूर्ण;

काष्ठा nfs4_get_lease_समय_res अणु
	काष्ठा nfs4_sequence_res	lr_seq_res;
	काष्ठा nfs_fsinfo	       *lr_fsinfo;
पूर्ण;

काष्ठा xdr_stream;
काष्ठा nfs4_xdr_opaque_data;

काष्ठा nfs4_xdr_opaque_ops अणु
	व्योम (*encode)(काष्ठा xdr_stream *, स्थिर व्योम *args,
			स्थिर काष्ठा nfs4_xdr_opaque_data *);
	व्योम (*मुक्त)(काष्ठा nfs4_xdr_opaque_data *);
पूर्ण;

काष्ठा nfs4_xdr_opaque_data अणु
	स्थिर काष्ठा nfs4_xdr_opaque_ops *ops;
	व्योम *data;
पूर्ण;

#घोषणा PNFS_LAYOUT_MAXSIZE 4096

काष्ठा nfs4_layoutdriver_data अणु
	काष्ठा page **pages;
	__u32 pglen;
	__u32 len;
पूर्ण;

काष्ठा pnfs_layout_range अणु
	u32 iomode;
	u64 offset;
	u64 length;
पूर्ण;

काष्ठा nfs4_layoutget_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	__u32 type;
	काष्ठा pnfs_layout_range range;
	__u64 minlength;
	__u32 maxcount;
	काष्ठा inode *inode;
	काष्ठा nfs_खोलो_context *ctx;
	nfs4_stateid stateid;
	काष्ठा nfs4_layoutdriver_data layout;
पूर्ण;

काष्ठा nfs4_layoutget_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	पूर्णांक status;
	__u32 वापस_on_बंद;
	काष्ठा pnfs_layout_range range;
	__u32 type;
	nfs4_stateid stateid;
	काष्ठा nfs4_layoutdriver_data *layoutp;
पूर्ण;

काष्ठा nfs4_layoutget अणु
	काष्ठा nfs4_layoutget_args args;
	काष्ठा nfs4_layoutget_res res;
	स्थिर काष्ठा cred *cred;
	gfp_t gfp_flags;
पूर्ण;

काष्ठा nfs4_getdeviceinfo_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	काष्ठा pnfs_device *pdev;
	__u32 notअगरy_types;
पूर्ण;

काष्ठा nfs4_getdeviceinfo_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	काष्ठा pnfs_device *pdev;
	__u32 notअगरication;
पूर्ण;

काष्ठा nfs4_layoutcommit_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	nfs4_stateid stateid;
	__u64 lastbytewritten;
	काष्ठा inode *inode;
	स्थिर u32 *biपंचांगask;
	माप_प्रकार layoutupdate_len;
	काष्ठा page *layoutupdate_page;
	काष्ठा page **layoutupdate_pages;
	__be32 *start_p;
पूर्ण;

काष्ठा nfs4_layoutcommit_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	काष्ठा nfs_fattr *fattr;
	स्थिर काष्ठा nfs_server *server;
	पूर्णांक status;
पूर्ण;

काष्ठा nfs4_layoutcommit_data अणु
	काष्ठा rpc_task task;
	काष्ठा nfs_fattr fattr;
	काष्ठा list_head lseg_list;
	स्थिर काष्ठा cred *cred;
	काष्ठा inode *inode;
	काष्ठा nfs4_layoutcommit_args args;
	काष्ठा nfs4_layoutcommit_res res;
पूर्ण;

काष्ठा nfs4_layoutवापस_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	काष्ठा pnfs_layout_hdr *layout;
	काष्ठा inode *inode;
	काष्ठा pnfs_layout_range range;
	nfs4_stateid stateid;
	__u32   layout_type;
	काष्ठा nfs4_xdr_opaque_data *ld_निजी;
पूर्ण;

काष्ठा nfs4_layoutवापस_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	u32 lrs_present;
	nfs4_stateid stateid;
पूर्ण;

काष्ठा nfs4_layoutवापस अणु
	काष्ठा nfs4_layoutवापस_args args;
	काष्ठा nfs4_layoutवापस_res res;
	स्थिर काष्ठा cred *cred;
	काष्ठा nfs_client *clp;
	काष्ठा inode *inode;
	पूर्णांक rpc_status;
	काष्ठा nfs4_xdr_opaque_data ld_निजी;
पूर्ण;

#घोषणा PNFS_LAYOUTSTATS_MAXSIZE 256

काष्ठा nfs42_layoutstat_args;
काष्ठा nfs42_layoutstat_devinfo;
प्रकार	व्योम (*layoutstats_encode_t)(काष्ठा xdr_stream *,
		काष्ठा nfs42_layoutstat_args *,
		काष्ठा nfs42_layoutstat_devinfo *);

/* Per file per deviceid layoutstats */
काष्ठा nfs42_layoutstat_devinfo अणु
	काष्ठा nfs4_deviceid dev_id;
	__u64 offset;
	__u64 length;
	__u64 पढ़ो_count;
	__u64 पढ़ो_bytes;
	__u64 ग_लिखो_count;
	__u64 ग_लिखो_bytes;
	__u32 layout_type;
	काष्ठा nfs4_xdr_opaque_data ld_निजी;
पूर्ण;

काष्ठा nfs42_layoutstat_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	काष्ठा nfs_fh *fh;
	काष्ठा inode *inode;
	nfs4_stateid stateid;
	पूर्णांक num_dev;
	काष्ठा nfs42_layoutstat_devinfo *devinfo;
पूर्ण;

काष्ठा nfs42_layoutstat_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	पूर्णांक num_dev;
	पूर्णांक rpc_status;
पूर्ण;

काष्ठा nfs42_layoutstat_data अणु
	काष्ठा inode *inode;
	काष्ठा nfs42_layoutstat_args args;
	काष्ठा nfs42_layoutstat_res res;
पूर्ण;

काष्ठा nfs42_device_error अणु
	काष्ठा nfs4_deviceid dev_id;
	पूर्णांक status;
	क्रमागत nfs_opnum4 opnum;
पूर्ण;

काष्ठा nfs42_layout_error अणु
	__u64 offset;
	__u64 length;
	nfs4_stateid stateid;
	काष्ठा nfs42_device_error errors[1];
पूर्ण;

#घोषणा NFS42_LAYOUTERROR_MAX 5

काष्ठा nfs42_layouterror_args अणु
	काष्ठा nfs4_sequence_args seq_args;
	काष्ठा inode *inode;
	अचिन्हित पूर्णांक num_errors;
	काष्ठा nfs42_layout_error errors[NFS42_LAYOUTERROR_MAX];
पूर्ण;

काष्ठा nfs42_layouterror_res अणु
	काष्ठा nfs4_sequence_res seq_res;
	अचिन्हित पूर्णांक num_errors;
	पूर्णांक rpc_status;
पूर्ण;

काष्ठा nfs42_layouterror_data अणु
	काष्ठा nfs42_layouterror_args args;
	काष्ठा nfs42_layouterror_res res;
	काष्ठा inode *inode;
	काष्ठा pnfs_layout_segment *lseg;
पूर्ण;

काष्ठा nfs42_clone_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh			*src_fh;
	काष्ठा nfs_fh			*dst_fh;
	nfs4_stateid			src_stateid;
	nfs4_stateid			dst_stateid;
	__u64				src_offset;
	__u64				dst_offset;
	__u64				count;
	स्थिर u32			*dst_biपंचांगask;
पूर्ण;

काष्ठा nfs42_clone_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	अचिन्हित पूर्णांक			rpc_status;
	काष्ठा nfs_fattr		*dst_fattr;
	स्थिर काष्ठा nfs_server		*server;
पूर्ण;

काष्ठा stateowner_id अणु
	__u64	create_समय;
	__u32	uniquअगरier;
पूर्ण;

/*
 * Arguments to the खोलो call.
 */
काष्ठा nfs_खोलोargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *	fh;
	काष्ठा nfs_seqid *	seqid;
	पूर्णांक			खोलो_flags;
	भ_शेषe_t			भ_शेषe;
	u32			share_access;
	u32			access;
	__u64                   clientid;
	काष्ठा stateowner_id	id;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा iattr *  attrs;    /* UNCHECKED, GUARDED, EXCLUSIVE4_1 */
			nfs4_verअगरier   verअगरier; /* EXCLUSIVE */
		पूर्ण;
		nfs4_stateid	delegation;		/* CLAIM_DELEGATE_CUR */
		भ_शेषe_t		delegation_type;	/* CLAIM_PREVIOUS */
	पूर्ण u;
	स्थिर काष्ठा qstr *	name;
	स्थिर काष्ठा nfs_server *server;	 /* Needed क्रम ID mapping */
	स्थिर u32 *		biपंचांगask;
	स्थिर u32 *		खोलो_biपंचांगap;
	क्रमागत खोलो_claim_type4	claim;
	क्रमागत createmode4	createmode;
	स्थिर काष्ठा nfs4_label *label;
	umode_t			umask;
	काष्ठा nfs4_layoutget_args *lg_args;
पूर्ण;

काष्ठा nfs_खोलोres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_stateid            stateid;
	काष्ठा nfs_fh           fh;
	काष्ठा nfs4_change_info	cinfo;
	__u32                   rflags;
	काष्ठा nfs_fattr *      f_attr;
	काष्ठा nfs4_label	*f_label;
	काष्ठा nfs_seqid *	seqid;
	स्थिर काष्ठा nfs_server *server;
	भ_शेषe_t			delegation_type;
	nfs4_stateid		delegation;
	अचिन्हित दीर्घ		pagemod_limit;
	__u32			करो_recall;
	__u32			attrset[NFS4_BITMAP_SIZE];
	काष्ठा nfs4_string	*owner;
	काष्ठा nfs4_string	*group_owner;
	__u32			access_request;
	__u32			access_supported;
	__u32			access_result;
	काष्ठा nfs4_layoutget_res *lg_res;
पूर्ण;

/*
 * Arguments to the खोलो_confirm call.
 */
काष्ठा nfs_खोलो_confirmargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *	fh;
	nfs4_stateid *		stateid;
	काष्ठा nfs_seqid *	seqid;
पूर्ण;

काष्ठा nfs_खोलो_confirmres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_stateid            stateid;
	काष्ठा nfs_seqid *	seqid;
पूर्ण;

/*
 * Arguments to the बंद call.
 */
काष्ठा nfs_बंदargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *         fh;
	nfs4_stateid 		stateid;
	काष्ठा nfs_seqid *	seqid;
	भ_शेषe_t			भ_शेषe;
	u32			share_access;
	स्थिर u32 *		biपंचांगask;
	u32			biपंचांगask_store[NFS_BITMASK_SZ];
	काष्ठा nfs4_layoutवापस_args *lr_args;
पूर्ण;

काष्ठा nfs_बंदres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_stateid            stateid;
	काष्ठा nfs_fattr *	fattr;
	काष्ठा nfs_seqid *	seqid;
	स्थिर काष्ठा nfs_server *server;
	काष्ठा nfs4_layoutवापस_res *lr_res;
	पूर्णांक lr_ret;
पूर्ण;
/*
 *  * Arguments to the lock,lockt, and locku call.
 *   */
काष्ठा nfs_lowner अणु
	__u64			clientid;
	__u64			id;
	dev_t			s_dev;
पूर्ण;

काष्ठा nfs_lock_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *		fh;
	काष्ठा file_lock *	fl;
	काष्ठा nfs_seqid *	lock_seqid;
	nfs4_stateid		lock_stateid;
	काष्ठा nfs_seqid *	खोलो_seqid;
	nfs4_stateid		खोलो_stateid;
	काष्ठा nfs_lowner	lock_owner;
	अचिन्हित अक्षर		block : 1;
	अचिन्हित अक्षर		reclaim : 1;
	अचिन्हित अक्षर		new_lock : 1;
	अचिन्हित अक्षर		new_lock_owner : 1;
पूर्ण;

काष्ठा nfs_lock_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_stateid		stateid;
	काष्ठा nfs_seqid *	lock_seqid;
	काष्ठा nfs_seqid *	खोलो_seqid;
पूर्ण;

काष्ठा nfs_locku_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *		fh;
	काष्ठा file_lock *	fl;
	काष्ठा nfs_seqid *	seqid;
	nfs4_stateid 		stateid;
पूर्ण;

काष्ठा nfs_locku_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_stateid		stateid;
	काष्ठा nfs_seqid *	seqid;
पूर्ण;

काष्ठा nfs_lockt_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *		fh;
	काष्ठा file_lock *	fl;
	काष्ठा nfs_lowner	lock_owner;
पूर्ण;

काष्ठा nfs_lockt_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा file_lock *	denied; /* LOCK, LOCKT failed */
पूर्ण;

काष्ठा nfs_release_lockowner_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_lowner	lock_owner;
पूर्ण;

काष्ठा nfs_release_lockowner_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
पूर्ण;

काष्ठा nfs4_delegवापसargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *fhandle;
	स्थिर nfs4_stateid *stateid;
	स्थिर u32 *biपंचांगask;
	u32 biपंचांगask_store[NFS_BITMASK_SZ];
	काष्ठा nfs4_layoutवापस_args *lr_args;
पूर्ण;

काष्ठा nfs4_delegवापसres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fattr * fattr;
	काष्ठा nfs_server *server;
	काष्ठा nfs4_layoutवापस_res *lr_res;
	पूर्णांक lr_ret;
पूर्ण;

/*
 * Arguments to the ग_लिखो call.
 */
काष्ठा nfs_ग_लिखो_verअगरier अणु
	अक्षर			data[8];
पूर्ण;

काष्ठा nfs_ग_लिखोverf अणु
	काष्ठा nfs_ग_लिखो_verअगरier verअगरier;
	क्रमागत nfs3_stable_how	committed;
पूर्ण;

/*
 * Arguments shared by the पढ़ो and ग_लिखो call.
 */
काष्ठा nfs_pgio_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *		fh;
	काष्ठा nfs_खोलो_context *context;
	काष्ठा nfs_lock_context *lock_context;
	nfs4_stateid		stateid;
	__u64			offset;
	__u32			count;
	अचिन्हित पूर्णांक		pgbase;
	काष्ठा page **		pages;
	जोड़ अणु
		अचिन्हित पूर्णांक		replen;			/* used by पढ़ो */
		काष्ठा अणु
			स्थिर u32 *		biपंचांगask;	/* used by ग_लिखो */
			u32 biपंचांगask_store[NFS_BITMASK_SZ];	/* used by ग_लिखो */
			क्रमागत nfs3_stable_how	stable;		/* used by ग_लिखो */
		पूर्ण;
	पूर्ण;
पूर्ण;

काष्ठा nfs_pgio_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fattr *	fattr;
	__u64			count;
	__u32			op_status;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक		replen;		/* used by पढ़ो */
			पूर्णांक			eof;		/* used by पढ़ो */
		पूर्ण;
		काष्ठा अणु
			काष्ठा nfs_ग_लिखोverf *	verf;		/* used by ग_लिखो */
			स्थिर काष्ठा nfs_server *server;	/* used by ग_लिखो */
		पूर्ण;
	पूर्ण;
पूर्ण;

/*
 * Arguments to the commit call.
 */
काष्ठा nfs_commitargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh		*fh;
	__u64			offset;
	__u32			count;
	स्थिर u32		*biपंचांगask;
पूर्ण;

काष्ठा nfs_commitres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	__u32			op_status;
	काष्ठा nfs_fattr	*fattr;
	काष्ठा nfs_ग_लिखोverf	*verf;
	स्थिर काष्ठा nfs_server *server;
पूर्ण;

/*
 * Common arguments to the unlink call
 */
काष्ठा nfs_हटाओargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh	*fh;
	काष्ठा qstr		name;
पूर्ण;

काष्ठा nfs_हटाओres अणु
	काष्ठा nfs4_sequence_res 	seq_res;
	काष्ठा nfs_server *server;
	काष्ठा nfs_fattr	*dir_attr;
	काष्ठा nfs4_change_info	cinfo;
पूर्ण;

/*
 * Common arguments to the नाम call
 */
काष्ठा nfs_नामargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh		*old_dir;
	स्थिर काष्ठा nfs_fh		*new_dir;
	स्थिर काष्ठा qstr		*old_name;
	स्थिर काष्ठा qstr		*new_name;
पूर्ण;

काष्ठा nfs_नामres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_server		*server;
	काष्ठा nfs4_change_info		old_cinfo;
	काष्ठा nfs_fattr		*old_fattr;
	काष्ठा nfs4_change_info		new_cinfo;
	काष्ठा nfs_fattr		*new_fattr;
पूर्ण;

/* parsed sec= options */
#घोषणा NFS_AUTH_INFO_MAX_FLAVORS 12 /* see fs/nfs/super.c */
काष्ठा nfs_auth_info अणु
	अचिन्हित पूर्णांक            flavor_len;
	rpc_authflavor_t        flavors[NFS_AUTH_INFO_MAX_FLAVORS];
पूर्ण;

/*
 * Argument काष्ठा क्रम decode_entry function
 */
काष्ठा nfs_entry अणु
	__u64			ino;
	__u64			cookie,
				prev_cookie;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
	पूर्णांक			eof;
	काष्ठा nfs_fh *		fh;
	काष्ठा nfs_fattr *	fattr;
	काष्ठा nfs4_label  *label;
	अचिन्हित अक्षर		d_type;
	काष्ठा nfs_server *	server;
पूर्ण;

काष्ठा nfs_सूची_पढ़ो_arg अणु
	काष्ठा dentry		*dentry;
	स्थिर काष्ठा cred	*cred;
	__be32			*verf;
	u64			cookie;
	काष्ठा page		**pages;
	अचिन्हित पूर्णांक		page_len;
	bool			plus;
पूर्ण;

काष्ठा nfs_सूची_पढ़ो_res अणु
	__be32			*verf;
पूर्ण;

/*
 * The following types are क्रम NFSv2 only.
 */
काष्ठा nfs_sattrargs अणु
	काष्ठा nfs_fh *		fh;
	काष्ठा iattr *		sattr;
पूर्ण;

काष्ठा nfs_diropargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा nfs_createargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
	काष्ठा iattr *		sattr;
पूर्ण;

काष्ठा nfs_setattrargs अणु
	काष्ठा nfs4_sequence_args 	seq_args;
	काष्ठा nfs_fh *                 fh;
	nfs4_stateid                    stateid;
	काष्ठा iattr *                  iap;
	स्थिर काष्ठा nfs_server *	server; /* Needed क्रम name mapping */
	स्थिर u32 *			biपंचांगask;
	स्थिर काष्ठा nfs4_label		*label;
पूर्ण;

काष्ठा nfs_setaclargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh *			fh;
	माप_प्रकार				acl_len;
	काष्ठा page **			acl_pages;
पूर्ण;

काष्ठा nfs_setaclres अणु
	काष्ठा nfs4_sequence_res	seq_res;
पूर्ण;

काष्ठा nfs_getaclargs अणु
	काष्ठा nfs4_sequence_args 	seq_args;
	काष्ठा nfs_fh *			fh;
	माप_प्रकार				acl_len;
	काष्ठा page **			acl_pages;
पूर्ण;

/* getxattr ACL पूर्णांकerface flags */
#घोषणा NFS4_ACL_TRUNC		0x0001	/* ACL was truncated */
काष्ठा nfs_getaclres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	माप_प्रकार				acl_len;
	माप_प्रकार				acl_data_offset;
	पूर्णांक				acl_flags;
	काष्ठा page *			acl_scratch;
पूर्ण;

काष्ठा nfs_setattrres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fattr *              fattr;
	काष्ठा nfs4_label		*label;
	स्थिर काष्ठा nfs_server *	server;
पूर्ण;

काष्ठा nfs_linkargs अणु
	काष्ठा nfs_fh *		fromfh;
	काष्ठा nfs_fh *		tofh;
	स्थिर अक्षर *		toname;
	अचिन्हित पूर्णांक		tolen;
पूर्ण;

काष्ठा nfs_symlinkargs अणु
	काष्ठा nfs_fh *		fromfh;
	स्थिर अक्षर *		fromname;
	अचिन्हित पूर्णांक		fromlen;
	काष्ठा page **		pages;
	अचिन्हित पूर्णांक		pathlen;
	काष्ठा iattr *		sattr;
पूर्ण;

काष्ठा nfs_सूची_पढ़ोargs अणु
	काष्ठा nfs_fh *		fh;
	__u32			cookie;
	अचिन्हित पूर्णांक		count;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs3_getaclargs अणु
	काष्ठा nfs_fh *		fh;
	पूर्णांक			mask;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs3_setaclargs अणु
	काष्ठा inode *		inode;
	पूर्णांक			mask;
	काष्ठा posix_acl *	acl_access;
	काष्ठा posix_acl *	acl_शेष;
	माप_प्रकार			len;
	अचिन्हित पूर्णांक		npages;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs_diropok अणु
	काष्ठा nfs_fh *		fh;
	काष्ठा nfs_fattr *	fattr;
पूर्ण;

काष्ठा nfs_पढ़ोlinkargs अणु
	काष्ठा nfs_fh *		fh;
	अचिन्हित पूर्णांक		pgbase;
	अचिन्हित पूर्णांक		pglen;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs3_sattrargs अणु
	काष्ठा nfs_fh *		fh;
	काष्ठा iattr *		sattr;
	अचिन्हित पूर्णांक		guard;
	काष्ठा बारpec64	guardसमय;
पूर्ण;

काष्ठा nfs3_diropargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
पूर्ण;

काष्ठा nfs3_accessargs अणु
	काष्ठा nfs_fh *		fh;
	__u32			access;
पूर्ण;

काष्ठा nfs3_createargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
	काष्ठा iattr *		sattr;
	क्रमागत nfs3_createmode	createmode;
	__be32			verअगरier[2];
पूर्ण;

काष्ठा nfs3_सूची_गढ़ोargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
	काष्ठा iattr *		sattr;
पूर्ण;

काष्ठा nfs3_symlinkargs अणु
	काष्ठा nfs_fh *		fromfh;
	स्थिर अक्षर *		fromname;
	अचिन्हित पूर्णांक		fromlen;
	काष्ठा page **		pages;
	अचिन्हित पूर्णांक		pathlen;
	काष्ठा iattr *		sattr;
पूर्ण;

काष्ठा nfs3_mknodargs अणु
	काष्ठा nfs_fh *		fh;
	स्थिर अक्षर *		name;
	अचिन्हित पूर्णांक		len;
	क्रमागत nfs3_ftype		type;
	काष्ठा iattr *		sattr;
	dev_t			rdev;
पूर्ण;

काष्ठा nfs3_linkargs अणु
	काष्ठा nfs_fh *		fromfh;
	काष्ठा nfs_fh *		tofh;
	स्थिर अक्षर *		toname;
	अचिन्हित पूर्णांक		tolen;
पूर्ण;

काष्ठा nfs3_सूची_पढ़ोargs अणु
	काष्ठा nfs_fh *		fh;
	__u64			cookie;
	__be32			verf[2];
	bool			plus;
	अचिन्हित पूर्णांक            count;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs3_diropres अणु
	काष्ठा nfs_fattr *	dir_attr;
	काष्ठा nfs_fh *		fh;
	काष्ठा nfs_fattr *	fattr;
पूर्ण;

काष्ठा nfs3_accessres अणु
	काष्ठा nfs_fattr *	fattr;
	__u32			access;
पूर्ण;

काष्ठा nfs3_पढ़ोlinkargs अणु
	काष्ठा nfs_fh *		fh;
	अचिन्हित पूर्णांक		pgbase;
	अचिन्हित पूर्णांक		pglen;
	काष्ठा page **		pages;
पूर्ण;

काष्ठा nfs3_linkres अणु
	काष्ठा nfs_fattr *	dir_attr;
	काष्ठा nfs_fattr *	fattr;
पूर्ण;

काष्ठा nfs3_सूची_पढ़ोres अणु
	काष्ठा nfs_fattr *	dir_attr;
	__be32 *		verf;
	bool			plus;
पूर्ण;

काष्ठा nfs3_getaclres अणु
	काष्ठा nfs_fattr *	fattr;
	पूर्णांक			mask;
	अचिन्हित पूर्णांक		acl_access_count;
	अचिन्हित पूर्णांक		acl_शेष_count;
	काष्ठा posix_acl *	acl_access;
	काष्ठा posix_acl *	acl_शेष;
पूर्ण;

#अगर IS_ENABLED(CONFIG_NFS_V4)

प्रकार u64 clientid4;

काष्ठा nfs4_accessargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर u32 *			biपंचांगask;
	u32				access;
पूर्ण;

काष्ठा nfs4_accessres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server *	server;
	काष्ठा nfs_fattr *		fattr;
	u32				supported;
	u32				access;
पूर्ण;

काष्ठा nfs4_create_arg अणु
	काष्ठा nfs4_sequence_args 	seq_args;
	u32				ftype;
	जोड़ अणु
		काष्ठा अणु
			काष्ठा page **	pages;
			अचिन्हित पूर्णांक	len;
		पूर्ण symlink;   /* NF4LNK */
		काष्ठा अणु
			u32		specdata1;
			u32		specdata2;
		पूर्ण device;    /* NF4BLK, NF4CHR */
	पूर्ण u;
	स्थिर काष्ठा qstr *		name;
	स्थिर काष्ठा nfs_server *	server;
	स्थिर काष्ठा iattr *		attrs;
	स्थिर काष्ठा nfs_fh *		dir_fh;
	स्थिर u32 *			biपंचांगask;
	स्थिर काष्ठा nfs4_label		*label;
	umode_t				umask;
पूर्ण;

काष्ठा nfs4_create_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server *	server;
	काष्ठा nfs_fh *			fh;
	काष्ठा nfs_fattr *		fattr;
	काष्ठा nfs4_label		*label;
	काष्ठा nfs4_change_info		dir_cinfo;
पूर्ण;

काष्ठा nfs4_fsinfo_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_fsinfo_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fsinfo	       *fsinfo;
पूर्ण;

काष्ठा nfs4_getattr_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_getattr_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server *	server;
	काष्ठा nfs_fattr *		fattr;
	काष्ठा nfs4_label		*label;
पूर्ण;

काष्ठा nfs4_link_arg अणु
	काष्ठा nfs4_sequence_args 	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर काष्ठा nfs_fh *		dir_fh;
	स्थिर काष्ठा qstr *		name;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_link_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server *	server;
	काष्ठा nfs_fattr *		fattr;
	काष्ठा nfs4_label		*label;
	काष्ठा nfs4_change_info		cinfo;
	काष्ठा nfs_fattr *		dir_attr;
पूर्ण;

काष्ठा nfs4_lookup_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		dir_fh;
	स्थिर काष्ठा qstr *		name;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_lookup_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server *	server;
	काष्ठा nfs_fattr *		fattr;
	काष्ठा nfs_fh *			fh;
	काष्ठा nfs4_label		*label;
पूर्ण;

काष्ठा nfs4_lookupp_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh		*fh;
	स्थिर u32			*biपंचांगask;
पूर्ण;

काष्ठा nfs4_lookupp_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	स्थिर काष्ठा nfs_server		*server;
	काष्ठा nfs_fattr		*fattr;
	काष्ठा nfs_fh			*fh;
	काष्ठा nfs4_label		*label;
पूर्ण;

काष्ठा nfs4_lookup_root_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_pathconf_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_pathconf_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_pathconf	       *pathconf;
पूर्ण;

काष्ठा nfs4_सूची_पढ़ो_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	u64				cookie;
	nfs4_verअगरier			verअगरier;
	u32				count;
	काष्ठा page **			pages;	/* zero-copy data */
	अचिन्हित पूर्णांक			pgbase;	/* zero-copy data */
	स्थिर u32 *			biपंचांगask;
	bool				plus;
पूर्ण;

काष्ठा nfs4_सूची_पढ़ो_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	nfs4_verअगरier			verअगरier;
	अचिन्हित पूर्णांक			pgbase;
पूर्ण;

काष्ठा nfs4_पढ़ोlink अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	अचिन्हित पूर्णांक			pgbase;
	अचिन्हित पूर्णांक			pglen;   /* zero-copy data */
	काष्ठा page **			pages;   /* zero-copy data */
पूर्ण;

काष्ठा nfs4_पढ़ोlink_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
पूर्ण;

काष्ठा nfs4_setclientid अणु
	स्थिर nfs4_verअगरier *		sc_verअगरier;
	u32				sc_prog;
	अचिन्हित पूर्णांक			sc_netid_len;
	अक्षर				sc_netid[RPCBIND_MAXNETIDLEN + 1];
	अचिन्हित पूर्णांक			sc_uaddr_len;
	अक्षर				sc_uaddr[RPCBIND_MAXUADDRLEN + 1];
	काष्ठा nfs_client		*sc_clnt;
	काष्ठा rpc_cred			*sc_cred;
पूर्ण;

काष्ठा nfs4_setclientid_res अणु
	u64				clientid;
	nfs4_verअगरier			confirm;
पूर्ण;

काष्ठा nfs4_statfs_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *		fh;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_statfs_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fsstat	       *fsstat;
पूर्ण;

काष्ठा nfs4_server_caps_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh		       *fhandle;
	स्थिर u32 *			biपंचांगask;
पूर्ण;

काष्ठा nfs4_server_caps_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	u32				attr_biपंचांगask[3];
	u32				exclcreat_biपंचांगask[3];
	u32				acl_biपंचांगask;
	u32				has_links;
	u32				has_symlinks;
	u32				fh_expire_type;
पूर्ण;

#घोषणा NFS4_PATHNAME_MAXCOMPONENTS 512
काष्ठा nfs4_pathname अणु
	अचिन्हित पूर्णांक ncomponents;
	काष्ठा nfs4_string components[NFS4_PATHNAME_MAXCOMPONENTS];
पूर्ण;

#घोषणा NFS4_FS_LOCATION_MAXSERVERS 10
काष्ठा nfs4_fs_location अणु
	अचिन्हित पूर्णांक nservers;
	काष्ठा nfs4_string servers[NFS4_FS_LOCATION_MAXSERVERS];
	काष्ठा nfs4_pathname rootpath;
पूर्ण;

#घोषणा NFS4_FS_LOCATIONS_MAXENTRIES 10
काष्ठा nfs4_fs_locations अणु
	काष्ठा nfs_fattr fattr;
	स्थिर काष्ठा nfs_server *server;
	काष्ठा nfs4_pathname fs_path;
	पूर्णांक nlocations;
	काष्ठा nfs4_fs_location locations[NFS4_FS_LOCATIONS_MAXENTRIES];
पूर्ण;

काष्ठा nfs4_fs_locations_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh *dir_fh;
	स्थिर काष्ठा nfs_fh *fh;
	स्थिर काष्ठा qstr *name;
	काष्ठा page *page;
	स्थिर u32 *biपंचांगask;
	clientid4 clientid;
	अचिन्हित अक्षर migration:1, renew:1;
पूर्ण;

काष्ठा nfs4_fs_locations_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs4_fs_locations       *fs_locations;
	अचिन्हित अक्षर			migration:1, renew:1;
पूर्ण;

काष्ठा nfs4_secinfo4 अणु
	u32			flavor;
	काष्ठा rpcsec_gss_info	flavor_info;
पूर्ण;

काष्ठा nfs4_secinfo_flavors अणु
	अचिन्हित पूर्णांक		num_flavors;
	काष्ठा nfs4_secinfo4	flavors[];
पूर्ण;

काष्ठा nfs4_secinfo_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh		*dir_fh;
	स्थिर काष्ठा qstr		*name;
पूर्ण;

काष्ठा nfs4_secinfo_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs4_secinfo_flavors	*flavors;
पूर्ण;

काष्ठा nfs4_fsid_present_arg अणु
	काष्ठा nfs4_sequence_args	seq_args;
	स्थिर काष्ठा nfs_fh		*fh;
	clientid4			clientid;
	अचिन्हित अक्षर			renew:1;
पूर्ण;

काष्ठा nfs4_fsid_present_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs_fh			*fh;
	अचिन्हित अक्षर			renew:1;
पूर्ण;

#पूर्ण_अगर /* CONFIG_NFS_V4 */

काष्ठा nfsसमय4 अणु
	u64	seconds;
	u32	nseconds;
पूर्ण;

#अगर_घोषित CONFIG_NFS_V4_1

काष्ठा pnfs_commit_bucket अणु
	काष्ठा list_head written;
	काष्ठा list_head committing;
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा nfs_ग_लिखोverf direct_verf;
पूर्ण;

काष्ठा pnfs_commit_array अणु
	काष्ठा list_head cinfo_list;
	काष्ठा list_head lseg_list;
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा rcu_head rcu;
	refcount_t refcount;
	अचिन्हित पूर्णांक nbuckets;
	काष्ठा pnfs_commit_bucket buckets[];
पूर्ण;

काष्ठा pnfs_ds_commit_info अणु
	काष्ठा list_head commits;
	अचिन्हित पूर्णांक nwritten;
	अचिन्हित पूर्णांक ncommitting;
	स्थिर काष्ठा pnfs_commit_ops *ops;
पूर्ण;

काष्ठा nfs41_state_protection अणु
	u32 how;
	काष्ठा nfs4_op_map enक्रमce;
	काष्ठा nfs4_op_map allow;
पूर्ण;

काष्ठा nfs41_exchange_id_args अणु
	काष्ठा nfs_client		*client;
	nfs4_verअगरier			verअगरier;
	u32				flags;
	काष्ठा nfs41_state_protection	state_protect;
पूर्ण;

काष्ठा nfs41_server_owner अणु
	uपूर्णांक64_t			minor_id;
	uपूर्णांक32_t			major_id_sz;
	अक्षर				major_id[NFS4_OPAQUE_LIMIT];
पूर्ण;

काष्ठा nfs41_server_scope अणु
	uपूर्णांक32_t			server_scope_sz;
	अक्षर 				server_scope[NFS4_OPAQUE_LIMIT];
पूर्ण;

काष्ठा nfs41_impl_id अणु
	अक्षर				करोमुख्य[NFS4_OPAQUE_LIMIT + 1];
	अक्षर				name[NFS4_OPAQUE_LIMIT + 1];
	काष्ठा nfsसमय4			date;
पूर्ण;

#घोषणा MAX_BIND_CONN_TO_SESSION_RETRIES 3
काष्ठा nfs41_bind_conn_to_session_args अणु
	काष्ठा nfs_client		*client;
	काष्ठा nfs4_sessionid		sessionid;
	u32				dir;
	bool				use_conn_in_rdma_mode;
	पूर्णांक				retries;
पूर्ण;

काष्ठा nfs41_bind_conn_to_session_res अणु
	काष्ठा nfs4_sessionid		sessionid;
	u32				dir;
	bool				use_conn_in_rdma_mode;
पूर्ण;

काष्ठा nfs41_exchange_id_res अणु
	u64				clientid;
	u32				seqid;
	u32				flags;
	काष्ठा nfs41_server_owner	*server_owner;
	काष्ठा nfs41_server_scope	*server_scope;
	काष्ठा nfs41_impl_id		*impl_id;
	काष्ठा nfs41_state_protection	state_protect;
पूर्ण;

काष्ठा nfs41_create_session_args अणु
	काष्ठा nfs_client	       *client;
	u64				clientid;
	uपूर्णांक32_t			seqid;
	uपूर्णांक32_t			flags;
	uपूर्णांक32_t			cb_program;
	काष्ठा nfs4_channel_attrs	fc_attrs;	/* Fore Channel */
	काष्ठा nfs4_channel_attrs	bc_attrs;	/* Back Channel */
पूर्ण;

काष्ठा nfs41_create_session_res अणु
	काष्ठा nfs4_sessionid		sessionid;
	uपूर्णांक32_t			seqid;
	uपूर्णांक32_t			flags;
	काष्ठा nfs4_channel_attrs	fc_attrs;	/* Fore Channel */
	काष्ठा nfs4_channel_attrs	bc_attrs;	/* Back Channel */
पूर्ण;

काष्ठा nfs41_reclaim_complete_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	/* In the future extend to include curr_fh क्रम use with migration */
	अचिन्हित अक्षर			one_fs:1;
पूर्ण;

काष्ठा nfs41_reclaim_complete_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
पूर्ण;

#घोषणा SECINFO_STYLE_CURRENT_FH 0
#घोषणा SECINFO_STYLE_PARENT 1
काष्ठा nfs41_secinfo_no_name_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	पूर्णांक				style;
पूर्ण;

काष्ठा nfs41_test_stateid_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	nfs4_stateid			*stateid;
पूर्ण;

काष्ठा nfs41_test_stateid_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	अचिन्हित पूर्णांक			status;
पूर्ण;

काष्ठा nfs41_मुक्त_stateid_args अणु
	काष्ठा nfs4_sequence_args	seq_args;
	nfs4_stateid			stateid;
पूर्ण;

काष्ठा nfs41_मुक्त_stateid_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	अचिन्हित पूर्णांक			status;
पूर्ण;

#अन्यथा

काष्ठा pnfs_ds_commit_info अणु
पूर्ण;

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

#अगर_घोषित CONFIG_NFS_V4_2
काष्ठा nfs42_falloc_args अणु
	काष्ठा nfs4_sequence_args	seq_args;

	काष्ठा nfs_fh			*falloc_fh;
	nfs4_stateid			 falloc_stateid;
	u64				 falloc_offset;
	u64				 falloc_length;
	स्थिर u32			*falloc_biपंचांगask;
पूर्ण;

काष्ठा nfs42_falloc_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	अचिन्हित पूर्णांक			status;

	काष्ठा nfs_fattr		*falloc_fattr;
	स्थिर काष्ठा nfs_server		*falloc_server;
पूर्ण;

काष्ठा nfs42_copy_args अणु
	काष्ठा nfs4_sequence_args	seq_args;

	काष्ठा nfs_fh			*src_fh;
	nfs4_stateid			src_stateid;
	u64				src_pos;

	काष्ठा nfs_fh			*dst_fh;
	nfs4_stateid			dst_stateid;
	u64				dst_pos;

	u64				count;
	bool				sync;
	काष्ठा nl4_server		*cp_src;
पूर्ण;

काष्ठा nfs42_ग_लिखो_res अणु
	nfs4_stateid		stateid;
	u64			count;
	काष्ठा nfs_ग_लिखोverf	verअगरier;
पूर्ण;

काष्ठा nfs42_copy_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs42_ग_लिखो_res		ग_लिखो_res;
	bool				consecutive;
	bool				synchronous;
	काष्ठा nfs_commitres		commit_res;
पूर्ण;

काष्ठा nfs42_offload_status_args अणु
	काष्ठा nfs4_sequence_args	osa_seq_args;
	काष्ठा nfs_fh			*osa_src_fh;
	nfs4_stateid			osa_stateid;
पूर्ण;

काष्ठा nfs42_offload_status_res अणु
	काष्ठा nfs4_sequence_res	osr_seq_res;
	uपूर्णांक64_t			osr_count;
	पूर्णांक				osr_status;
पूर्ण;

काष्ठा nfs42_copy_notअगरy_args अणु
	काष्ठा nfs4_sequence_args	cna_seq_args;

	काष्ठा nfs_fh		*cna_src_fh;
	nfs4_stateid		cna_src_stateid;
	काष्ठा nl4_server	cna_dst;
पूर्ण;

काष्ठा nfs42_copy_notअगरy_res अणु
	काष्ठा nfs4_sequence_res	cnr_seq_res;

	काष्ठा nfsसमय4		cnr_lease_समय;
	nfs4_stateid		cnr_stateid;
	काष्ठा nl4_server	cnr_src;
पूर्ण;

काष्ठा nfs42_seek_args अणु
	काष्ठा nfs4_sequence_args	seq_args;

	काष्ठा nfs_fh			*sa_fh;
	nfs4_stateid			sa_stateid;
	u64				sa_offset;
	u32				sa_what;
पूर्ण;

काष्ठा nfs42_seek_res अणु
	काष्ठा nfs4_sequence_res	seq_res;
	अचिन्हित पूर्णांक			status;

	u32	sr_eof;
	u64	sr_offset;
पूर्ण;

काष्ठा nfs42_setxattrargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh			*fh;
	स्थिर अक्षर			*xattr_name;
	u32				xattr_flags;
	माप_प्रकार				xattr_len;
	काष्ठा page			**xattr_pages;
पूर्ण;

काष्ठा nfs42_setxattrres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs4_change_info		cinfo;
पूर्ण;

काष्ठा nfs42_getxattrargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh			*fh;
	स्थिर अक्षर			*xattr_name;
	माप_प्रकार				xattr_len;
	काष्ठा page			**xattr_pages;
पूर्ण;

काष्ठा nfs42_getxattrres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	माप_प्रकार				xattr_len;
पूर्ण;

काष्ठा nfs42_listxattrsargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh			*fh;
	u32				count;
	u64				cookie;
	काष्ठा page			**xattr_pages;
पूर्ण;

काष्ठा nfs42_listxattrsres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा page			*scratch;
	व्योम				*xattr_buf;
	माप_प्रकार				xattr_len;
	u64				cookie;
	bool				eof;
	माप_प्रकार				copied;
पूर्ण;

काष्ठा nfs42_हटाओxattrargs अणु
	काष्ठा nfs4_sequence_args	seq_args;
	काष्ठा nfs_fh			*fh;
	स्थिर अक्षर			*xattr_name;
पूर्ण;

काष्ठा nfs42_हटाओxattrres अणु
	काष्ठा nfs4_sequence_res	seq_res;
	काष्ठा nfs4_change_info		cinfo;
पूर्ण;

#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

काष्ठा nfs_page;

#घोषणा NFS_PAGEVEC_SIZE	(8U)

काष्ठा nfs_page_array अणु
	काष्ठा page		**pagevec;
	अचिन्हित पूर्णांक		npages;		/* Max length of pagevec */
	काष्ठा page		*page_array[NFS_PAGEVEC_SIZE];
पूर्ण;

/* used as flag bits in nfs_pgio_header */
क्रमागत अणु
	NFS_IOHDR_ERROR = 0,
	NFS_IOHDR_खातापूर्ण,
	NFS_IOHDR_REDO,
	NFS_IOHDR_STAT,
	NFS_IOHDR_RESEND_PNFS,
	NFS_IOHDR_RESEND_MDS,
पूर्ण;

काष्ठा nfs_io_completion;
काष्ठा nfs_pgio_header अणु
	काष्ठा inode		*inode;
	स्थिर काष्ठा cred		*cred;
	काष्ठा list_head	pages;
	काष्ठा nfs_page		*req;
	काष्ठा nfs_ग_लिखोverf	verf;		/* Used क्रम ग_लिखोs */
	भ_शेषe_t			rw_mode;
	काष्ठा pnfs_layout_segment *lseg;
	loff_t			io_start;
	स्थिर काष्ठा rpc_call_ops *mds_ops;
	व्योम (*release) (काष्ठा nfs_pgio_header *hdr);
	स्थिर काष्ठा nfs_pgio_completion_ops *completion_ops;
	स्थिर काष्ठा nfs_rw_ops	*rw_ops;
	काष्ठा nfs_io_completion *io_completion;
	काष्ठा nfs_direct_req	*dreq;

	पूर्णांक			pnfs_error;
	पूर्णांक			error;		/* merge with pnfs_error */
	अचिन्हित पूर्णांक		good_bytes;	/* boundary of good data */
	अचिन्हित दीर्घ		flags;

	/*
	 * rpc data
	 */
	काष्ठा rpc_task		task;
	काष्ठा nfs_fattr	fattr;
	काष्ठा nfs_pgio_args	args;		/* argument काष्ठा */
	काष्ठा nfs_pgio_res	res;		/* result काष्ठा */
	अचिन्हित दीर्घ		बारtamp;	/* For lease renewal */
	पूर्णांक (*pgio_करोne_cb)(काष्ठा rpc_task *, काष्ठा nfs_pgio_header *);
	__u64			mds_offset;	/* Filelayout dense stripe */
	काष्ठा nfs_page_array	page_array;
	काष्ठा nfs_client	*ds_clp;	/* pNFS data server */
	u32			ds_commit_idx;	/* ds index अगर ds_clp is set */
	u32			pgio_mirror_idx;/* mirror index in pgio layer */
पूर्ण;

काष्ठा nfs_mds_commit_info अणु
	atomic_t rpcs_out;
	atomic_दीर्घ_t		ncommit;
	काष्ठा list_head	list;
पूर्ण;

काष्ठा nfs_commit_info;
काष्ठा nfs_commit_data;
काष्ठा nfs_inode;
काष्ठा nfs_commit_completion_ops अणु
	व्योम (*completion) (काष्ठा nfs_commit_data *data);
	व्योम (*resched_ग_लिखो) (काष्ठा nfs_commit_info *, काष्ठा nfs_page *);
पूर्ण;

काष्ठा nfs_commit_info अणु
	काष्ठा inode 			*inode;	/* Needed क्रम inode->i_lock */
	काष्ठा nfs_mds_commit_info	*mds;
	काष्ठा pnfs_ds_commit_info	*ds;
	काष्ठा nfs_direct_req		*dreq;	/* O_सूचीECT request */
	स्थिर काष्ठा nfs_commit_completion_ops *completion_ops;
पूर्ण;

काष्ठा nfs_commit_data अणु
	काष्ठा rpc_task		task;
	काष्ठा inode		*inode;
	स्थिर काष्ठा cred		*cred;
	काष्ठा nfs_fattr	fattr;
	काष्ठा nfs_ग_लिखोverf	verf;
	काष्ठा list_head	pages;		/* Coalesced requests we wish to flush */
	काष्ठा list_head	list;		/* lists of काष्ठा nfs_ग_लिखो_data */
	काष्ठा nfs_direct_req	*dreq;		/* O_सूचीECT request */
	काष्ठा nfs_commitargs	args;		/* argument काष्ठा */
	काष्ठा nfs_commitres	res;		/* result काष्ठा */
	काष्ठा nfs_खोलो_context *context;
	काष्ठा pnfs_layout_segment *lseg;
	काष्ठा nfs_client	*ds_clp;	/* pNFS data server */
	पूर्णांक			ds_commit_index;
	loff_t			lwb;
	स्थिर काष्ठा rpc_call_ops *mds_ops;
	स्थिर काष्ठा nfs_commit_completion_ops *completion_ops;
	पूर्णांक (*commit_करोne_cb) (काष्ठा rpc_task *task, काष्ठा nfs_commit_data *data);
	अचिन्हित दीर्घ		flags;
पूर्ण;

काष्ठा nfs_pgio_completion_ops अणु
	व्योम	(*error_cleanup)(काष्ठा list_head *head, पूर्णांक);
	व्योम	(*init_hdr)(काष्ठा nfs_pgio_header *hdr);
	व्योम	(*completion)(काष्ठा nfs_pgio_header *hdr);
	व्योम	(*reschedule_io)(काष्ठा nfs_pgio_header *hdr);
पूर्ण;

काष्ठा nfs_unlinkdata अणु
	काष्ठा nfs_हटाओargs args;
	काष्ठा nfs_हटाओres res;
	काष्ठा dentry *dentry;
	रुको_queue_head_t wq;
	स्थिर काष्ठा cred *cred;
	काष्ठा nfs_fattr dir_attr;
	दीर्घ समयout;
पूर्ण;

काष्ठा nfs_नामdata अणु
	काष्ठा nfs_नामargs	args;
	काष्ठा nfs_नामres	res;
	स्थिर काष्ठा cred	*cred;
	काष्ठा inode		*old_dir;
	काष्ठा dentry		*old_dentry;
	काष्ठा nfs_fattr	old_fattr;
	काष्ठा inode		*new_dir;
	काष्ठा dentry		*new_dentry;
	काष्ठा nfs_fattr	new_fattr;
	व्योम (*complete)(काष्ठा rpc_task *, काष्ठा nfs_नामdata *);
	दीर्घ समयout;
	bool cancelled;
पूर्ण;

काष्ठा nfs_access_entry;
काष्ठा nfs_client;
काष्ठा rpc_समयout;
काष्ठा nfs_subversion;
काष्ठा nfs_mount_info;
काष्ठा nfs_client_initdata;
काष्ठा nfs_pageio_descriptor;
काष्ठा fs_context;

/*
 * RPC procedure vector क्रम NFSv2/NFSv3 demuxing
 */
काष्ठा nfs_rpc_ops अणु
	u32	version;		/* Protocol version */
	स्थिर काष्ठा dentry_operations *dentry_ops;
	स्थिर काष्ठा inode_operations *dir_inode_ops;
	स्थिर काष्ठा inode_operations *file_inode_ops;
	स्थिर काष्ठा file_operations *file_ops;
	स्थिर काष्ठा nlmclnt_operations *nlmclnt_ops;

	पूर्णांक	(*getroot) (काष्ठा nfs_server *, काष्ठा nfs_fh *,
			    काष्ठा nfs_fsinfo *);
	पूर्णांक	(*submount) (काष्ठा fs_context *, काष्ठा nfs_server *);
	पूर्णांक	(*try_get_tree) (काष्ठा fs_context *);
	पूर्णांक	(*getattr) (काष्ठा nfs_server *, काष्ठा nfs_fh *,
			    काष्ठा nfs_fattr *, काष्ठा nfs4_label *,
			    काष्ठा inode *);
	पूर्णांक	(*setattr) (काष्ठा dentry *, काष्ठा nfs_fattr *,
			    काष्ठा iattr *);
	पूर्णांक	(*lookup)  (काष्ठा inode *, काष्ठा dentry *,
			    काष्ठा nfs_fh *, काष्ठा nfs_fattr *,
			    काष्ठा nfs4_label *);
	पूर्णांक	(*lookupp) (काष्ठा inode *, काष्ठा nfs_fh *,
			    काष्ठा nfs_fattr *, काष्ठा nfs4_label *);
	पूर्णांक	(*access)  (काष्ठा inode *, काष्ठा nfs_access_entry *);
	पूर्णांक	(*पढ़ोlink)(काष्ठा inode *, काष्ठा page *, अचिन्हित पूर्णांक,
			    अचिन्हित पूर्णांक);
	पूर्णांक	(*create)  (काष्ठा inode *, काष्ठा dentry *,
			    काष्ठा iattr *, पूर्णांक);
	पूर्णांक	(*हटाओ)  (काष्ठा inode *, काष्ठा dentry *);
	व्योम	(*unlink_setup)  (काष्ठा rpc_message *, काष्ठा dentry *, काष्ठा inode *);
	व्योम	(*unlink_rpc_prepare) (काष्ठा rpc_task *, काष्ठा nfs_unlinkdata *);
	पूर्णांक	(*unlink_करोne) (काष्ठा rpc_task *, काष्ठा inode *);
	व्योम	(*नाम_setup)  (काष्ठा rpc_message *msg,
			काष्ठा dentry *old_dentry,
			काष्ठा dentry *new_dentry);
	व्योम	(*नाम_rpc_prepare)(काष्ठा rpc_task *task, काष्ठा nfs_नामdata *);
	पूर्णांक	(*नाम_करोne) (काष्ठा rpc_task *task, काष्ठा inode *old_dir, काष्ठा inode *new_dir);
	पूर्णांक	(*link)    (काष्ठा inode *, काष्ठा inode *, स्थिर काष्ठा qstr *);
	पूर्णांक	(*symlink) (काष्ठा inode *, काष्ठा dentry *, काष्ठा page *,
			    अचिन्हित पूर्णांक, काष्ठा iattr *);
	पूर्णांक	(*सूची_गढ़ो)   (काष्ठा inode *, काष्ठा dentry *, काष्ठा iattr *);
	पूर्णांक	(*सूची_हटाओ)   (काष्ठा inode *, स्थिर काष्ठा qstr *);
	पूर्णांक	(*सूची_पढ़ो) (काष्ठा nfs_सूची_पढ़ो_arg *, काष्ठा nfs_सूची_पढ़ो_res *);
	पूर्णांक	(*mknod)   (काष्ठा inode *, काष्ठा dentry *, काष्ठा iattr *,
			    dev_t);
	पूर्णांक	(*statfs)  (काष्ठा nfs_server *, काष्ठा nfs_fh *,
			    काष्ठा nfs_fsstat *);
	पूर्णांक	(*fsinfo)  (काष्ठा nfs_server *, काष्ठा nfs_fh *,
			    काष्ठा nfs_fsinfo *);
	पूर्णांक	(*pathconf) (काष्ठा nfs_server *, काष्ठा nfs_fh *,
			     काष्ठा nfs_pathconf *);
	पूर्णांक	(*set_capabilities)(काष्ठा nfs_server *, काष्ठा nfs_fh *);
	पूर्णांक	(*decode_dirent)(काष्ठा xdr_stream *, काष्ठा nfs_entry *, bool);
	पूर्णांक	(*pgio_rpc_prepare)(काष्ठा rpc_task *,
				    काष्ठा nfs_pgio_header *);
	व्योम	(*पढ़ो_setup)(काष्ठा nfs_pgio_header *, काष्ठा rpc_message *);
	पूर्णांक	(*पढ़ो_करोne)(काष्ठा rpc_task *, काष्ठा nfs_pgio_header *);
	व्योम	(*ग_लिखो_setup)(काष्ठा nfs_pgio_header *, काष्ठा rpc_message *,
				काष्ठा rpc_clnt **);
	पूर्णांक	(*ग_लिखो_करोne)(काष्ठा rpc_task *, काष्ठा nfs_pgio_header *);
	व्योम	(*commit_setup) (काष्ठा nfs_commit_data *, काष्ठा rpc_message *,
				काष्ठा rpc_clnt **);
	व्योम	(*commit_rpc_prepare)(काष्ठा rpc_task *, काष्ठा nfs_commit_data *);
	पूर्णांक	(*commit_करोne) (काष्ठा rpc_task *, काष्ठा nfs_commit_data *);
	पूर्णांक	(*lock)(काष्ठा file *, पूर्णांक, काष्ठा file_lock *);
	पूर्णांक	(*lock_check_bounds)(स्थिर काष्ठा file_lock *);
	व्योम	(*clear_acl_cache)(काष्ठा inode *);
	व्योम	(*बंद_context)(काष्ठा nfs_खोलो_context *ctx, पूर्णांक);
	काष्ठा inode * (*खोलो_context) (काष्ठा inode *dir,
				काष्ठा nfs_खोलो_context *ctx,
				पूर्णांक खोलो_flags,
				काष्ठा iattr *iattr,
				पूर्णांक *);
	पूर्णांक (*have_delegation)(काष्ठा inode *, भ_शेषe_t);
	काष्ठा nfs_client *(*alloc_client) (स्थिर काष्ठा nfs_client_initdata *);
	काष्ठा nfs_client *(*init_client) (काष्ठा nfs_client *,
				स्थिर काष्ठा nfs_client_initdata *);
	व्योम	(*मुक्त_client) (काष्ठा nfs_client *);
	काष्ठा nfs_server *(*create_server)(काष्ठा fs_context *);
	काष्ठा nfs_server *(*clone_server)(काष्ठा nfs_server *, काष्ठा nfs_fh *,
					   काष्ठा nfs_fattr *, rpc_authflavor_t);
पूर्ण;

/*
 * 	NFS_CALL(getattr, inode, (fattr));
 * पूर्णांकo
 *	NFS_PROTO(inode)->getattr(fattr);
 */
#घोषणा NFS_CALL(op, inode, args)	NFS_PROTO(inode)->op args

/*
 * Function vectors etc. क्रम the NFS client
 */
बाह्य स्थिर काष्ठा nfs_rpc_ops	nfs_v2_clientops;
बाह्य स्थिर काष्ठा nfs_rpc_ops	nfs_v3_clientops;
बाह्य स्थिर काष्ठा nfs_rpc_ops	nfs_v4_clientops;
बाह्य स्थिर काष्ठा rpc_version nfs_version2;
बाह्य स्थिर काष्ठा rpc_version nfs_version3;
बाह्य स्थिर काष्ठा rpc_version nfs_version4;

बाह्य स्थिर काष्ठा rpc_version nfsacl_version3;
बाह्य स्थिर काष्ठा rpc_program nfsacl_program;

#पूर्ण_अगर
