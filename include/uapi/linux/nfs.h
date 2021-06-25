<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * NFS protocol definitions
 *
 * This file contains स्थिरants mostly क्रम Version 2 of the protocol,
 * but also has a couple of NFSv3 bits in (notably the error codes).
 */
#अगर_अघोषित _UAPI_LINUX_NFS_H
#घोषणा _UAPI_LINUX_NFS_H

#समावेश <linux/types.h>

#घोषणा NFS_PROGRAM	100003
#घोषणा NFS_PORT	2049
#घोषणा NFS_RDMA_PORT	20049
#घोषणा NFS_MAXDATA	8192
#घोषणा NFS_MAXPATHLEN	1024
#घोषणा NFS_MAXNAMLEN	255
#घोषणा NFS_MAXGROUPS	16
#घोषणा NFS_FHSIZE	32
#घोषणा NFS_COOKIESIZE	4
#घोषणा NFS_FIFO_DEV	(-1)
#घोषणा NFSMODE_FMT	0170000
#घोषणा NFSMODE_सूची	0040000
#घोषणा NFSMODE_CHR	0020000
#घोषणा NFSMODE_BLK	0060000
#घोषणा NFSMODE_REG	0100000
#घोषणा NFSMODE_LNK	0120000
#घोषणा NFSMODE_SOCK	0140000
#घोषणा NFSMODE_FIFO	0010000

#घोषणा NFS_MNT_PROGRAM		100005
#घोषणा NFS_MNT_VERSION		1
#घोषणा NFS_MNT3_VERSION	3

#घोषणा NFS_PIPE_सूचीNAME "nfs"

/*
 * NFS stats. The good thing with these values is that NFSv3 errors are
 * a superset of NFSv2 errors (with the exception of NFSERR_WFLUSH which
 * no-one uses anyway), so we can happily mix code as दीर्घ as we make sure
 * no NFSv3 errors are वापसed to NFSv2 clients.
 * Error codes that have a `--' in the v2 column are not part of the
 * standard, but seem to be widely used nevertheless.
 */
 क्रमागत nfs_stat अणु
	NFS_OK = 0,			/* v2 v3 v4 */
	NFSERR_PERM = 1,		/* v2 v3 v4 */
	NFSERR_NOENT = 2,		/* v2 v3 v4 */
	NFSERR_IO = 5,			/* v2 v3 v4 */
	NFSERR_NXIO = 6,		/* v2 v3 v4 */
	NFSERR_EAGAIN = 11,		/* v2 v3 */
	NFSERR_ACCES = 13,		/* v2 v3 v4 */
	NFSERR_EXIST = 17,		/* v2 v3 v4 */
	NFSERR_XDEV = 18,		/*    v3 v4 */
	NFSERR_NODEV = 19,		/* v2 v3 v4 */
	NFSERR_NOTसूची = 20,		/* v2 v3 v4 */
	NFSERR_ISसूची = 21,		/* v2 v3 v4 */
	NFSERR_INVAL = 22,		/* v2 v3 v4 */
	NFSERR_FBIG = 27,		/* v2 v3 v4 */
	NFSERR_NOSPC = 28,		/* v2 v3 v4 */
	NFSERR_ROFS = 30,		/* v2 v3 v4 */
	NFSERR_MLINK = 31,		/*    v3 v4 */
	NFSERR_OPNOTSUPP = 45,		/* v2 v3 */
	NFSERR_NAMETOOLONG = 63,	/* v2 v3 v4 */
	NFSERR_NOTEMPTY = 66,		/* v2 v3 v4 */
	NFSERR_DQUOT = 69,		/* v2 v3 v4 */
	NFSERR_STALE = 70,		/* v2 v3 v4 */
	NFSERR_REMOTE = 71,		/* v2 v3 */
	NFSERR_WFLUSH = 99,		/* v2    */
	NFSERR_BADHANDLE = 10001,	/*    v3 v4 */
	NFSERR_NOT_SYNC = 10002,	/*    v3 */
	NFSERR_BAD_COOKIE = 10003,	/*    v3 v4 */
	NFSERR_NOTSUPP = 10004,		/*    v3 v4 */
	NFSERR_TOOSMALL = 10005,	/*    v3 v4 */
	NFSERR_SERVERFAULT = 10006,	/*    v3 v4 */
	NFSERR_BADTYPE = 10007,		/*    v3 v4 */
	NFSERR_JUKEBOX = 10008,		/*    v3 v4 */
	NFSERR_SAME = 10009,		/*       v4 */
	NFSERR_DENIED = 10010,		/*       v4 */
	NFSERR_EXPIRED = 10011,		/*       v4 */
	NFSERR_LOCKED = 10012,		/*       v4 */
	NFSERR_GRACE = 10013,		/*       v4 */
	NFSERR_FHEXPIRED = 10014,	/*       v4 */
	NFSERR_SHARE_DENIED = 10015,	/*       v4 */
	NFSERR_WRONGSEC = 10016,	/*       v4 */
	NFSERR_CLID_INUSE = 10017,	/*       v4 */
	NFSERR_RESOURCE = 10018,	/*       v4 */
	NFSERR_MOVED = 10019,		/*       v4 */
	NFSERR_NOखाताHANDLE = 10020,	/*       v4 */
	NFSERR_MINOR_VERS_MISMATCH = 10021,   /* v4 */
	NFSERR_STALE_CLIENTID = 10022,	/*       v4 */
	NFSERR_STALE_STATEID = 10023,   /*       v4 */
	NFSERR_OLD_STATEID = 10024,     /*       v4 */
	NFSERR_BAD_STATEID = 10025,     /*       v4 */  
	NFSERR_BAD_SEQID = 10026,	/*       v4 */
	NFSERR_NOT_SAME = 10027,	/*       v4 */
	NFSERR_LOCK_RANGE = 10028,	/*       v4 */
	NFSERR_SYMLINK = 10029,		/*       v4 */
	NFSERR_RESTOREFH = 10030,	/*       v4 */
	NFSERR_LEASE_MOVED = 10031,	/*       v4 */
	NFSERR_ATTRNOTSUPP = 10032,	/*       v4 */
	NFSERR_NO_GRACE = 10033,	/*       v4 */
	NFSERR_RECLAIM_BAD = 10034,	/*       v4 */
	NFSERR_RECLAIM_CONFLICT = 10035,/*       v4 */
	NFSERR_BAD_XDR = 10036,		/*       v4 */
	NFSERR_LOCKS_HELD = 10037,	/*       v4 */
	NFSERR_OPENMODE = 10038,       /*       v4 */
	NFSERR_BADOWNER = 10039,       /*       v4 */
	NFSERR_BADCHAR = 10040,        /*       v4 */
	NFSERR_BADNAME = 10041,        /*       v4 */
	NFSERR_BAD_RANGE = 10042,      /*       v4 */
	NFSERR_LOCK_NOTSUPP = 10043,   /*       v4 */
	NFSERR_OP_ILLEGAL = 10044,     /*       v4 */
	NFSERR_DEADLOCK = 10045,       /*       v4 */
	NFSERR_खाता_OPEN = 10046,      /*       v4 */
	NFSERR_ADMIN_REVOKED = 10047,  /*       v4 */
	NFSERR_CB_PATH_DOWN = 10048,   /*       v4 */
पूर्ण;

/* NFSv2 file types - beware, these are not the same in NFSv3 */

क्रमागत nfs_ftype अणु
	NFNON = 0,
	NFREG = 1,
	NFसूची = 2,
	NFBLK = 3,
	NFCHR = 4,
	NFLNK = 5,
	NFSOCK = 6,
	NFBAD = 7,
	NFFIFO = 8
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_NFS_H */
