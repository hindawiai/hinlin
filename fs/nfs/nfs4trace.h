<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Trond Myklebust <Trond.Myklebust@netapp.com>
 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM nfs4

#अगर !defined(_TRACE_NFS4_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_NFS4_H

#समावेश <linux/tracepoपूर्णांक.h>

TRACE_DEFINE_ENUM(EPERM);
TRACE_DEFINE_ENUM(ENOENT);
TRACE_DEFINE_ENUM(EIO);
TRACE_DEFINE_ENUM(ENXIO);
TRACE_DEFINE_ENUM(EACCES);
TRACE_DEFINE_ENUM(EEXIST);
TRACE_DEFINE_ENUM(EXDEV);
TRACE_DEFINE_ENUM(ENOTसूची);
TRACE_DEFINE_ENUM(EISसूची);
TRACE_DEFINE_ENUM(EFBIG);
TRACE_DEFINE_ENUM(ENOSPC);
TRACE_DEFINE_ENUM(EROFS);
TRACE_DEFINE_ENUM(EMLINK);
TRACE_DEFINE_ENUM(ENAMETOOLONG);
TRACE_DEFINE_ENUM(ENOTEMPTY);
TRACE_DEFINE_ENUM(EDQUOT);
TRACE_DEFINE_ENUM(ESTALE);
TRACE_DEFINE_ENUM(EBADHANDLE);
TRACE_DEFINE_ENUM(EBADCOOKIE);
TRACE_DEFINE_ENUM(ENOTSUPP);
TRACE_DEFINE_ENUM(ETOOSMALL);
TRACE_DEFINE_ENUM(EREMOTEIO);
TRACE_DEFINE_ENUM(EBADTYPE);
TRACE_DEFINE_ENUM(EAGAIN);
TRACE_DEFINE_ENUM(ELOOP);
TRACE_DEFINE_ENUM(EOPNOTSUPP);
TRACE_DEFINE_ENUM(EDEADLK);
TRACE_DEFINE_ENUM(ENOMEM);
TRACE_DEFINE_ENUM(EKEYEXPIRED);
TRACE_DEFINE_ENUM(ETIMEDOUT);
TRACE_DEFINE_ENUM(ERESTARTSYS);
TRACE_DEFINE_ENUM(ECONNREFUSED);
TRACE_DEFINE_ENUM(ECONNRESET);
TRACE_DEFINE_ENUM(ENETUNREACH);
TRACE_DEFINE_ENUM(EHOSTUNREACH);
TRACE_DEFINE_ENUM(EHOSTDOWN);
TRACE_DEFINE_ENUM(EPIPE);
TRACE_DEFINE_ENUM(EPFNOSUPPORT);
TRACE_DEFINE_ENUM(EPROTONOSUPPORT);

TRACE_DEFINE_ENUM(NFS4_OK);
TRACE_DEFINE_ENUM(NFS4ERR_ACCESS);
TRACE_DEFINE_ENUM(NFS4ERR_ATTRNOTSUPP);
TRACE_DEFINE_ENUM(NFS4ERR_ADMIN_REVOKED);
TRACE_DEFINE_ENUM(NFS4ERR_BACK_CHAN_BUSY);
TRACE_DEFINE_ENUM(NFS4ERR_BADCHAR);
TRACE_DEFINE_ENUM(NFS4ERR_BADHANDLE);
TRACE_DEFINE_ENUM(NFS4ERR_BADIOMODE);
TRACE_DEFINE_ENUM(NFS4ERR_BADLAYOUT);
TRACE_DEFINE_ENUM(NFS4ERR_BADLABEL);
TRACE_DEFINE_ENUM(NFS4ERR_BADNAME);
TRACE_DEFINE_ENUM(NFS4ERR_BADOWNER);
TRACE_DEFINE_ENUM(NFS4ERR_BADSESSION);
TRACE_DEFINE_ENUM(NFS4ERR_BADSLOT);
TRACE_DEFINE_ENUM(NFS4ERR_BADTYPE);
TRACE_DEFINE_ENUM(NFS4ERR_BADXDR);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_COOKIE);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_HIGH_SLOT);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_RANGE);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_SEQID);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_SESSION_DIGEST);
TRACE_DEFINE_ENUM(NFS4ERR_BAD_STATEID);
TRACE_DEFINE_ENUM(NFS4ERR_CB_PATH_DOWN);
TRACE_DEFINE_ENUM(NFS4ERR_CLID_INUSE);
TRACE_DEFINE_ENUM(NFS4ERR_CLIENTID_BUSY);
TRACE_DEFINE_ENUM(NFS4ERR_COMPLETE_ALREADY);
TRACE_DEFINE_ENUM(NFS4ERR_CONN_NOT_BOUND_TO_SESSION);
TRACE_DEFINE_ENUM(NFS4ERR_DEADLOCK);
TRACE_DEFINE_ENUM(NFS4ERR_DEADSESSION);
TRACE_DEFINE_ENUM(NFS4ERR_DELAY);
TRACE_DEFINE_ENUM(NFS4ERR_DELEG_ALREADY_WANTED);
TRACE_DEFINE_ENUM(NFS4ERR_DELEG_REVOKED);
TRACE_DEFINE_ENUM(NFS4ERR_DENIED);
TRACE_DEFINE_ENUM(NFS4ERR_सूचीDELEG_UNAVAIL);
TRACE_DEFINE_ENUM(NFS4ERR_DQUOT);
TRACE_DEFINE_ENUM(NFS4ERR_ENCR_ALG_UNSUPP);
TRACE_DEFINE_ENUM(NFS4ERR_EXIST);
TRACE_DEFINE_ENUM(NFS4ERR_EXPIRED);
TRACE_DEFINE_ENUM(NFS4ERR_FBIG);
TRACE_DEFINE_ENUM(NFS4ERR_FHEXPIRED);
TRACE_DEFINE_ENUM(NFS4ERR_खाता_OPEN);
TRACE_DEFINE_ENUM(NFS4ERR_GRACE);
TRACE_DEFINE_ENUM(NFS4ERR_HASH_ALG_UNSUPP);
TRACE_DEFINE_ENUM(NFS4ERR_INVAL);
TRACE_DEFINE_ENUM(NFS4ERR_IO);
TRACE_DEFINE_ENUM(NFS4ERR_ISसूची);
TRACE_DEFINE_ENUM(NFS4ERR_LAYOUTTRYLATER);
TRACE_DEFINE_ENUM(NFS4ERR_LAYOUTUNAVAILABLE);
TRACE_DEFINE_ENUM(NFS4ERR_LEASE_MOVED);
TRACE_DEFINE_ENUM(NFS4ERR_LOCKED);
TRACE_DEFINE_ENUM(NFS4ERR_LOCKS_HELD);
TRACE_DEFINE_ENUM(NFS4ERR_LOCK_RANGE);
TRACE_DEFINE_ENUM(NFS4ERR_MINOR_VERS_MISMATCH);
TRACE_DEFINE_ENUM(NFS4ERR_MLINK);
TRACE_DEFINE_ENUM(NFS4ERR_MOVED);
TRACE_DEFINE_ENUM(NFS4ERR_NAMETOOLONG);
TRACE_DEFINE_ENUM(NFS4ERR_NOENT);
TRACE_DEFINE_ENUM(NFS4ERR_NOखाताHANDLE);
TRACE_DEFINE_ENUM(NFS4ERR_NOMATCHING_LAYOUT);
TRACE_DEFINE_ENUM(NFS4ERR_NOSPC);
TRACE_DEFINE_ENUM(NFS4ERR_NOTसूची);
TRACE_DEFINE_ENUM(NFS4ERR_NOTEMPTY);
TRACE_DEFINE_ENUM(NFS4ERR_NOTSUPP);
TRACE_DEFINE_ENUM(NFS4ERR_NOT_ONLY_OP);
TRACE_DEFINE_ENUM(NFS4ERR_NOT_SAME);
TRACE_DEFINE_ENUM(NFS4ERR_NO_GRACE);
TRACE_DEFINE_ENUM(NFS4ERR_NXIO);
TRACE_DEFINE_ENUM(NFS4ERR_OLD_STATEID);
TRACE_DEFINE_ENUM(NFS4ERR_OPENMODE);
TRACE_DEFINE_ENUM(NFS4ERR_OP_ILLEGAL);
TRACE_DEFINE_ENUM(NFS4ERR_OP_NOT_IN_SESSION);
TRACE_DEFINE_ENUM(NFS4ERR_PERM);
TRACE_DEFINE_ENUM(NFS4ERR_PNFS_IO_HOLE);
TRACE_DEFINE_ENUM(NFS4ERR_PNFS_NO_LAYOUT);
TRACE_DEFINE_ENUM(NFS4ERR_RECALLCONFLICT);
TRACE_DEFINE_ENUM(NFS4ERR_RECLAIM_BAD);
TRACE_DEFINE_ENUM(NFS4ERR_RECLAIM_CONFLICT);
TRACE_DEFINE_ENUM(NFS4ERR_REJECT_DELEG);
TRACE_DEFINE_ENUM(NFS4ERR_REP_TOO_BIG);
TRACE_DEFINE_ENUM(NFS4ERR_REP_TOO_BIG_TO_CACHE);
TRACE_DEFINE_ENUM(NFS4ERR_REQ_TOO_BIG);
TRACE_DEFINE_ENUM(NFS4ERR_RESOURCE);
TRACE_DEFINE_ENUM(NFS4ERR_RESTOREFH);
TRACE_DEFINE_ENUM(NFS4ERR_RETRY_UNCACHED_REP);
TRACE_DEFINE_ENUM(NFS4ERR_RETURNCONFLICT);
TRACE_DEFINE_ENUM(NFS4ERR_ROFS);
TRACE_DEFINE_ENUM(NFS4ERR_SAME);
TRACE_DEFINE_ENUM(NFS4ERR_SHARE_DENIED);
TRACE_DEFINE_ENUM(NFS4ERR_SEQUENCE_POS);
TRACE_DEFINE_ENUM(NFS4ERR_SEQ_FALSE_RETRY);
TRACE_DEFINE_ENUM(NFS4ERR_SEQ_MISORDERED);
TRACE_DEFINE_ENUM(NFS4ERR_SERVERFAULT);
TRACE_DEFINE_ENUM(NFS4ERR_STALE);
TRACE_DEFINE_ENUM(NFS4ERR_STALE_CLIENTID);
TRACE_DEFINE_ENUM(NFS4ERR_STALE_STATEID);
TRACE_DEFINE_ENUM(NFS4ERR_SYMLINK);
TRACE_DEFINE_ENUM(NFS4ERR_TOOSMALL);
TRACE_DEFINE_ENUM(NFS4ERR_TOO_MANY_OPS);
TRACE_DEFINE_ENUM(NFS4ERR_UNKNOWN_LAYOUTTYPE);
TRACE_DEFINE_ENUM(NFS4ERR_UNSAFE_COMPOUND);
TRACE_DEFINE_ENUM(NFS4ERR_WRONGSEC);
TRACE_DEFINE_ENUM(NFS4ERR_WRONG_CRED);
TRACE_DEFINE_ENUM(NFS4ERR_WRONG_TYPE);
TRACE_DEFINE_ENUM(NFS4ERR_XDEV);

TRACE_DEFINE_ENUM(NFS4ERR_RESET_TO_MDS);
TRACE_DEFINE_ENUM(NFS4ERR_RESET_TO_PNFS);

#घोषणा show_nfsv4_errors(error) \
	__prपूर्णांक_symbolic(error, \
		अणु NFS4_OK, "OK" पूर्ण, \
		/* Mapped by nfs4_stat_to_त्रुटि_सं() */ \
		अणु EPERM, "EPERM" पूर्ण, \
		अणु ENOENT, "ENOENT" पूर्ण, \
		अणु EIO, "EIO" पूर्ण, \
		अणु ENXIO, "ENXIO" पूर्ण, \
		अणु EACCES, "EACCES" पूर्ण, \
		अणु EEXIST, "EEXIST" पूर्ण, \
		अणु EXDEV, "EXDEV" पूर्ण, \
		अणु ENOTसूची, "ENOTDIR" पूर्ण, \
		अणु EISसूची, "EISDIR" पूर्ण, \
		अणु EFBIG, "EFBIG" पूर्ण, \
		अणु ENOSPC, "ENOSPC" पूर्ण, \
		अणु EROFS, "EROFS" पूर्ण, \
		अणु EMLINK, "EMLINK" पूर्ण, \
		अणु ENAMETOOLONG, "ENAMETOOLONG" पूर्ण, \
		अणु ENOTEMPTY, "ENOTEMPTY" पूर्ण, \
		अणु EDQUOT, "EDQUOT" पूर्ण, \
		अणु ESTALE, "ESTALE" पूर्ण, \
		अणु EBADHANDLE, "EBADHANDLE" पूर्ण, \
		अणु EBADCOOKIE, "EBADCOOKIE" पूर्ण, \
		अणु ENOTSUPP, "ENOTSUPP" पूर्ण, \
		अणु ETOOSMALL, "ETOOSMALL" पूर्ण, \
		अणु EREMOTEIO, "EREMOTEIO" पूर्ण, \
		अणु EBADTYPE, "EBADTYPE" पूर्ण, \
		अणु EAGAIN, "EAGAIN" पूर्ण, \
		अणु ELOOP, "ELOOP" पूर्ण, \
		अणु EOPNOTSUPP, "EOPNOTSUPP" पूर्ण, \
		अणु EDEADLK, "EDEADLK" पूर्ण, \
		/* RPC errors */ \
		अणु ENOMEM, "ENOMEM" पूर्ण, \
		अणु EKEYEXPIRED, "EKEYEXPIRED" पूर्ण, \
		अणु ETIMEDOUT, "ETIMEDOUT" पूर्ण, \
		अणु ERESTARTSYS, "ERESTARTSYS" पूर्ण, \
		अणु ECONNREFUSED, "ECONNREFUSED" पूर्ण, \
		अणु ECONNRESET, "ECONNRESET" पूर्ण, \
		अणु ENETUNREACH, "ENETUNREACH" पूर्ण, \
		अणु EHOSTUNREACH, "EHOSTUNREACH" पूर्ण, \
		अणु EHOSTDOWN, "EHOSTDOWN" पूर्ण, \
		अणु EPIPE, "EPIPE" पूर्ण, \
		अणु EPFNOSUPPORT, "EPFNOSUPPORT" पूर्ण, \
		अणु EPROTONOSUPPORT, "EPROTONOSUPPORT" पूर्ण, \
		/* NFSv4 native errors */ \
		अणु NFS4ERR_ACCESS, "ACCESS" पूर्ण, \
		अणु NFS4ERR_ATTRNOTSUPP, "ATTRNOTSUPP" पूर्ण, \
		अणु NFS4ERR_ADMIN_REVOKED, "ADMIN_REVOKED" पूर्ण, \
		अणु NFS4ERR_BACK_CHAN_BUSY, "BACK_CHAN_BUSY" पूर्ण, \
		अणु NFS4ERR_BADCHAR, "BADCHAR" पूर्ण, \
		अणु NFS4ERR_BADHANDLE, "BADHANDLE" पूर्ण, \
		अणु NFS4ERR_BADIOMODE, "BADIOMODE" पूर्ण, \
		अणु NFS4ERR_BADLAYOUT, "BADLAYOUT" पूर्ण, \
		अणु NFS4ERR_BADLABEL, "BADLABEL" पूर्ण, \
		अणु NFS4ERR_BADNAME, "BADNAME" पूर्ण, \
		अणु NFS4ERR_BADOWNER, "BADOWNER" पूर्ण, \
		अणु NFS4ERR_BADSESSION, "BADSESSION" पूर्ण, \
		अणु NFS4ERR_BADSLOT, "BADSLOT" पूर्ण, \
		अणु NFS4ERR_BADTYPE, "BADTYPE" पूर्ण, \
		अणु NFS4ERR_BADXDR, "BADXDR" पूर्ण, \
		अणु NFS4ERR_BAD_COOKIE, "BAD_COOKIE" पूर्ण, \
		अणु NFS4ERR_BAD_HIGH_SLOT, "BAD_HIGH_SLOT" पूर्ण, \
		अणु NFS4ERR_BAD_RANGE, "BAD_RANGE" पूर्ण, \
		अणु NFS4ERR_BAD_SEQID, "BAD_SEQID" पूर्ण, \
		अणु NFS4ERR_BAD_SESSION_DIGEST, "BAD_SESSION_DIGEST" पूर्ण, \
		अणु NFS4ERR_BAD_STATEID, "BAD_STATEID" पूर्ण, \
		अणु NFS4ERR_CB_PATH_DOWN, "CB_PATH_DOWN" पूर्ण, \
		अणु NFS4ERR_CLID_INUSE, "CLID_INUSE" पूर्ण, \
		अणु NFS4ERR_CLIENTID_BUSY, "CLIENTID_BUSY" पूर्ण, \
		अणु NFS4ERR_COMPLETE_ALREADY, "COMPLETE_ALREADY" पूर्ण, \
		अणु NFS4ERR_CONN_NOT_BOUND_TO_SESSION, \
			"CONN_NOT_BOUND_TO_SESSION" पूर्ण, \
		अणु NFS4ERR_DEADLOCK, "DEADLOCK" पूर्ण, \
		अणु NFS4ERR_DEADSESSION, "DEAD_SESSION" पूर्ण, \
		अणु NFS4ERR_DELAY, "DELAY" पूर्ण, \
		अणु NFS4ERR_DELEG_ALREADY_WANTED, \
			"DELEG_ALREADY_WANTED" पूर्ण, \
		अणु NFS4ERR_DELEG_REVOKED, "DELEG_REVOKED" पूर्ण, \
		अणु NFS4ERR_DENIED, "DENIED" पूर्ण, \
		अणु NFS4ERR_सूचीDELEG_UNAVAIL, "DIRDELEG_UNAVAIL" पूर्ण, \
		अणु NFS4ERR_DQUOT, "DQUOT" पूर्ण, \
		अणु NFS4ERR_ENCR_ALG_UNSUPP, "ENCR_ALG_UNSUPP" पूर्ण, \
		अणु NFS4ERR_EXIST, "EXIST" पूर्ण, \
		अणु NFS4ERR_EXPIRED, "EXPIRED" पूर्ण, \
		अणु NFS4ERR_FBIG, "FBIG" पूर्ण, \
		अणु NFS4ERR_FHEXPIRED, "FHEXPIRED" पूर्ण, \
		अणु NFS4ERR_खाता_OPEN, "FILE_OPEN" पूर्ण, \
		अणु NFS4ERR_GRACE, "GRACE" पूर्ण, \
		अणु NFS4ERR_HASH_ALG_UNSUPP, "HASH_ALG_UNSUPP" पूर्ण, \
		अणु NFS4ERR_INVAL, "INVAL" पूर्ण, \
		अणु NFS4ERR_IO, "IO" पूर्ण, \
		अणु NFS4ERR_ISसूची, "ISDIR" पूर्ण, \
		अणु NFS4ERR_LAYOUTTRYLATER, "LAYOUTTRYLATER" पूर्ण, \
		अणु NFS4ERR_LAYOUTUNAVAILABLE, "LAYOUTUNAVAILABLE" पूर्ण, \
		अणु NFS4ERR_LEASE_MOVED, "LEASE_MOVED" पूर्ण, \
		अणु NFS4ERR_LOCKED, "LOCKED" पूर्ण, \
		अणु NFS4ERR_LOCKS_HELD, "LOCKS_HELD" पूर्ण, \
		अणु NFS4ERR_LOCK_RANGE, "LOCK_RANGE" पूर्ण, \
		अणु NFS4ERR_MINOR_VERS_MISMATCH, "MINOR_VERS_MISMATCH" पूर्ण, \
		अणु NFS4ERR_MLINK, "MLINK" पूर्ण, \
		अणु NFS4ERR_MOVED, "MOVED" पूर्ण, \
		अणु NFS4ERR_NAMETOOLONG, "NAMETOOLONG" पूर्ण, \
		अणु NFS4ERR_NOENT, "NOENT" पूर्ण, \
		अणु NFS4ERR_NOखाताHANDLE, "NOFILEHANDLE" पूर्ण, \
		अणु NFS4ERR_NOMATCHING_LAYOUT, "NOMATCHING_LAYOUT" पूर्ण, \
		अणु NFS4ERR_NOSPC, "NOSPC" पूर्ण, \
		अणु NFS4ERR_NOTसूची, "NOTDIR" पूर्ण, \
		अणु NFS4ERR_NOTEMPTY, "NOTEMPTY" पूर्ण, \
		अणु NFS4ERR_NOTSUPP, "NOTSUPP" पूर्ण, \
		अणु NFS4ERR_NOT_ONLY_OP, "NOT_ONLY_OP" पूर्ण, \
		अणु NFS4ERR_NOT_SAME, "NOT_SAME" पूर्ण, \
		अणु NFS4ERR_NO_GRACE, "NO_GRACE" पूर्ण, \
		अणु NFS4ERR_NXIO, "NXIO" पूर्ण, \
		अणु NFS4ERR_OLD_STATEID, "OLD_STATEID" पूर्ण, \
		अणु NFS4ERR_OPENMODE, "OPENMODE" पूर्ण, \
		अणु NFS4ERR_OP_ILLEGAL, "OP_ILLEGAL" पूर्ण, \
		अणु NFS4ERR_OP_NOT_IN_SESSION, "OP_NOT_IN_SESSION" पूर्ण, \
		अणु NFS4ERR_PERM, "PERM" पूर्ण, \
		अणु NFS4ERR_PNFS_IO_HOLE, "PNFS_IO_HOLE" पूर्ण, \
		अणु NFS4ERR_PNFS_NO_LAYOUT, "PNFS_NO_LAYOUT" पूर्ण, \
		अणु NFS4ERR_RECALLCONFLICT, "RECALLCONFLICT" पूर्ण, \
		अणु NFS4ERR_RECLAIM_BAD, "RECLAIM_BAD" पूर्ण, \
		अणु NFS4ERR_RECLAIM_CONFLICT, "RECLAIM_CONFLICT" पूर्ण, \
		अणु NFS4ERR_REJECT_DELEG, "REJECT_DELEG" पूर्ण, \
		अणु NFS4ERR_REP_TOO_BIG, "REP_TOO_BIG" पूर्ण, \
		अणु NFS4ERR_REP_TOO_BIG_TO_CACHE, \
			"REP_TOO_BIG_TO_CACHE" पूर्ण, \
		अणु NFS4ERR_REQ_TOO_BIG, "REQ_TOO_BIG" पूर्ण, \
		अणु NFS4ERR_RESOURCE, "RESOURCE" पूर्ण, \
		अणु NFS4ERR_RESTOREFH, "RESTOREFH" पूर्ण, \
		अणु NFS4ERR_RETRY_UNCACHED_REP, "RETRY_UNCACHED_REP" पूर्ण, \
		अणु NFS4ERR_RETURNCONFLICT, "RETURNCONFLICT" पूर्ण, \
		अणु NFS4ERR_ROFS, "ROFS" पूर्ण, \
		अणु NFS4ERR_SAME, "SAME" पूर्ण, \
		अणु NFS4ERR_SHARE_DENIED, "SHARE_DENIED" पूर्ण, \
		अणु NFS4ERR_SEQUENCE_POS, "SEQUENCE_POS" पूर्ण, \
		अणु NFS4ERR_SEQ_FALSE_RETRY, "SEQ_FALSE_RETRY" पूर्ण, \
		अणु NFS4ERR_SEQ_MISORDERED, "SEQ_MISORDERED" पूर्ण, \
		अणु NFS4ERR_SERVERFAULT, "SERVERFAULT" पूर्ण, \
		अणु NFS4ERR_STALE, "STALE" पूर्ण, \
		अणु NFS4ERR_STALE_CLIENTID, "STALE_CLIENTID" पूर्ण, \
		अणु NFS4ERR_STALE_STATEID, "STALE_STATEID" पूर्ण, \
		अणु NFS4ERR_SYMLINK, "SYMLINK" पूर्ण, \
		अणु NFS4ERR_TOOSMALL, "TOOSMALL" पूर्ण, \
		अणु NFS4ERR_TOO_MANY_OPS, "TOO_MANY_OPS" पूर्ण, \
		अणु NFS4ERR_UNKNOWN_LAYOUTTYPE, "UNKNOWN_LAYOUTTYPE" पूर्ण, \
		अणु NFS4ERR_UNSAFE_COMPOUND, "UNSAFE_COMPOUND" पूर्ण, \
		अणु NFS4ERR_WRONGSEC, "WRONGSEC" पूर्ण, \
		अणु NFS4ERR_WRONG_CRED, "WRONG_CRED" पूर्ण, \
		अणु NFS4ERR_WRONG_TYPE, "WRONG_TYPE" पूर्ण, \
		अणु NFS4ERR_XDEV, "XDEV" पूर्ण, \
		/* ***** Internal to Linux NFS client ***** */ \
		अणु NFS4ERR_RESET_TO_MDS, "RESET_TO_MDS" पूर्ण, \
		अणु NFS4ERR_RESET_TO_PNFS, "RESET_TO_PNFS" पूर्ण)

#घोषणा show_खोलो_flags(flags) \
	__prपूर्णांक_flags(flags, "|", \
		अणु O_CREAT, "O_CREAT" पूर्ण, \
		अणु O_EXCL, "O_EXCL" पूर्ण, \
		अणु O_TRUNC, "O_TRUNC" पूर्ण, \
		अणु O_सूचीECT, "O_DIRECT" पूर्ण)

#घोषणा show_भ_शेषe_flags(mode) \
	__prपूर्णांक_flags(mode, "|", \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_READ), "READ" पूर्ण, \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_WRITE), "WRITE" पूर्ण, \
		अणु ((__क्रमce अचिन्हित दीर्घ)FMODE_EXEC), "EXEC" पूर्ण)

#घोषणा show_nfs_fattr_flags(valid) \
	__prपूर्णांक_flags((अचिन्हित दीर्घ)valid, "|", \
		अणु NFS_ATTR_FATTR_TYPE, "TYPE" पूर्ण, \
		अणु NFS_ATTR_FATTR_MODE, "MODE" पूर्ण, \
		अणु NFS_ATTR_FATTR_NLINK, "NLINK" पूर्ण, \
		अणु NFS_ATTR_FATTR_OWNER, "OWNER" पूर्ण, \
		अणु NFS_ATTR_FATTR_GROUP, "GROUP" पूर्ण, \
		अणु NFS_ATTR_FATTR_RDEV, "RDEV" पूर्ण, \
		अणु NFS_ATTR_FATTR_SIZE, "SIZE" पूर्ण, \
		अणु NFS_ATTR_FATTR_FSID, "FSID" पूर्ण, \
		अणु NFS_ATTR_FATTR_खाताID, "FILEID" पूर्ण, \
		अणु NFS_ATTR_FATTR_ATIME, "ATIME" पूर्ण, \
		अणु NFS_ATTR_FATTR_MTIME, "MTIME" पूर्ण, \
		अणु NFS_ATTR_FATTR_CTIME, "CTIME" पूर्ण, \
		अणु NFS_ATTR_FATTR_CHANGE, "CHANGE" पूर्ण, \
		अणु NFS_ATTR_FATTR_OWNER_NAME, "OWNER_NAME" पूर्ण, \
		अणु NFS_ATTR_FATTR_GROUP_NAME, "GROUP_NAME" पूर्ण)

DECLARE_EVENT_CLASS(nfs4_clientid_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp,
			पूर्णांक error
		),

		TP_ARGS(clp, error),

		TP_STRUCT__entry(
			__string(dstaddr, clp->cl_hostname)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->error = error < 0 ? -error : 0;
			__assign_str(dstaddr, clp->cl_hostname);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) dstaddr=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			__get_str(dstaddr)
		)
);
#घोषणा DEFINE_NFS4_CLIENTID_EVENT(name) \
	DEFINE_EVENT(nfs4_clientid_event, name,	 \
			TP_PROTO( \
				स्थिर काष्ठा nfs_client *clp, \
				पूर्णांक error \
			), \
			TP_ARGS(clp, error))
DEFINE_NFS4_CLIENTID_EVENT(nfs4_setclientid);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_setclientid_confirm);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_renew);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_renew_async);
#अगर_घोषित CONFIG_NFS_V4_1
DEFINE_NFS4_CLIENTID_EVENT(nfs4_exchange_id);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_create_session);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_destroy_session);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_destroy_clientid);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_bind_conn_to_session);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_sequence);
DEFINE_NFS4_CLIENTID_EVENT(nfs4_reclaim_complete);

#घोषणा show_nfs4_sequence_status_flags(status) \
	__prपूर्णांक_flags((अचिन्हित दीर्घ)status, "|", \
		अणु SEQ4_STATUS_CB_PATH_DOWN, "CB_PATH_DOWN" पूर्ण, \
		अणु SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRING, \
			"CB_GSS_CONTEXTS_EXPIRING" पूर्ण, \
		अणु SEQ4_STATUS_CB_GSS_CONTEXTS_EXPIRED, \
			"CB_GSS_CONTEXTS_EXPIRED" पूर्ण, \
		अणु SEQ4_STATUS_EXPIRED_ALL_STATE_REVOKED, \
			"EXPIRED_ALL_STATE_REVOKED" पूर्ण, \
		अणु SEQ4_STATUS_EXPIRED_SOME_STATE_REVOKED, \
			"EXPIRED_SOME_STATE_REVOKED" पूर्ण, \
		अणु SEQ4_STATUS_ADMIN_STATE_REVOKED, \
			"ADMIN_STATE_REVOKED" पूर्ण, \
		अणु SEQ4_STATUS_RECALLABLE_STATE_REVOKED,	 \
			"RECALLABLE_STATE_REVOKED" पूर्ण, \
		अणु SEQ4_STATUS_LEASE_MOVED, "LEASE_MOVED" पूर्ण, \
		अणु SEQ4_STATUS_RESTART_RECLAIM_NEEDED, \
			"RESTART_RECLAIM_NEEDED" पूर्ण, \
		अणु SEQ4_STATUS_CB_PATH_DOWN_SESSION, \
			"CB_PATH_DOWN_SESSION" पूर्ण, \
		अणु SEQ4_STATUS_BACKCHANNEL_FAULT, \
			"BACKCHANNEL_FAULT" पूर्ण)

TRACE_EVENT(nfs4_sequence_करोne,
		TP_PROTO(
			स्थिर काष्ठा nfs4_session *session,
			स्थिर काष्ठा nfs4_sequence_res *res
		),
		TP_ARGS(session, res),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, session)
			__field(अचिन्हित पूर्णांक, slot_nr)
			__field(अचिन्हित पूर्णांक, seq_nr)
			__field(अचिन्हित पूर्णांक, highest_slotid)
			__field(अचिन्हित पूर्णांक, target_highest_slotid)
			__field(अचिन्हित पूर्णांक, status_flags)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs4_slot *sr_slot = res->sr_slot;
			__entry->session = nfs_session_id_hash(&session->sess_id);
			__entry->slot_nr = sr_slot->slot_nr;
			__entry->seq_nr = sr_slot->seq_nr;
			__entry->highest_slotid = res->sr_highest_slotid;
			__entry->target_highest_slotid =
					res->sr_target_highest_slotid;
			__entry->status_flags = res->sr_status_flags;
			__entry->error = res->sr_status < 0 ?
					-res->sr_status : 0;
		),
		TP_prपूर्णांकk(
			"error=%ld (%s) session=0x%08x slot_nr=%u seq_nr=%u "
			"highest_slotid=%u target_highest_slotid=%u "
			"status_flags=%u (%s)",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			__entry->session,
			__entry->slot_nr,
			__entry->seq_nr,
			__entry->highest_slotid,
			__entry->target_highest_slotid,
			__entry->status_flags,
			show_nfs4_sequence_status_flags(__entry->status_flags)
		)
);

काष्ठा cb_sequenceargs;
काष्ठा cb_sequenceres;

TRACE_EVENT(nfs4_cb_sequence,
		TP_PROTO(
			स्थिर काष्ठा cb_sequenceargs *args,
			स्थिर काष्ठा cb_sequenceres *res,
			__be32 status
		),
		TP_ARGS(args, res, status),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, session)
			__field(अचिन्हित पूर्णांक, slot_nr)
			__field(अचिन्हित पूर्णांक, seq_nr)
			__field(अचिन्हित पूर्णांक, highest_slotid)
			__field(अचिन्हित पूर्णांक, cachethis)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->session = nfs_session_id_hash(&args->csa_sessionid);
			__entry->slot_nr = args->csa_slotid;
			__entry->seq_nr = args->csa_sequenceid;
			__entry->highest_slotid = args->csa_highestslotid;
			__entry->cachethis = args->csa_cachethis;
			__entry->error = be32_to_cpu(status);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) session=0x%08x slot_nr=%u seq_nr=%u "
			"highest_slotid=%u",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			__entry->session,
			__entry->slot_nr,
			__entry->seq_nr,
			__entry->highest_slotid
		)
);

TRACE_EVENT(nfs4_cb_seqid_err,
		TP_PROTO(
			स्थिर काष्ठा cb_sequenceargs *args,
			__be32 status
		),
		TP_ARGS(args, status),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, session)
			__field(अचिन्हित पूर्णांक, slot_nr)
			__field(अचिन्हित पूर्णांक, seq_nr)
			__field(अचिन्हित पूर्णांक, highest_slotid)
			__field(अचिन्हित पूर्णांक, cachethis)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->session = nfs_session_id_hash(&args->csa_sessionid);
			__entry->slot_nr = args->csa_slotid;
			__entry->seq_nr = args->csa_sequenceid;
			__entry->highest_slotid = args->csa_highestslotid;
			__entry->cachethis = args->csa_cachethis;
			__entry->error = be32_to_cpu(status);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) session=0x%08x slot_nr=%u seq_nr=%u "
			"highest_slotid=%u",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			__entry->session,
			__entry->slot_nr,
			__entry->seq_nr,
			__entry->highest_slotid
		)
);

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

TRACE_EVENT(nfs4_setup_sequence,
		TP_PROTO(
			स्थिर काष्ठा nfs4_session *session,
			स्थिर काष्ठा nfs4_sequence_args *args
		),
		TP_ARGS(session, args),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, session)
			__field(अचिन्हित पूर्णांक, slot_nr)
			__field(अचिन्हित पूर्णांक, seq_nr)
			__field(अचिन्हित पूर्णांक, highest_used_slotid)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs4_slot *sa_slot = args->sa_slot;
			__entry->session = session ? nfs_session_id_hash(&session->sess_id) : 0;
			__entry->slot_nr = sa_slot->slot_nr;
			__entry->seq_nr = sa_slot->seq_nr;
			__entry->highest_used_slotid =
					sa_slot->table->highest_used_slotid;
		),
		TP_prपूर्णांकk(
			"session=0x%08x slot_nr=%u seq_nr=%u "
			"highest_used_slotid=%u",
			__entry->session,
			__entry->slot_nr,
			__entry->seq_nr,
			__entry->highest_used_slotid
		)
);

TRACE_DEFINE_ENUM(NFS4CLNT_MANAGER_RUNNING);
TRACE_DEFINE_ENUM(NFS4CLNT_CHECK_LEASE);
TRACE_DEFINE_ENUM(NFS4CLNT_LEASE_EXPIRED);
TRACE_DEFINE_ENUM(NFS4CLNT_RECLAIM_REBOOT);
TRACE_DEFINE_ENUM(NFS4CLNT_RECLAIM_NOGRACE);
TRACE_DEFINE_ENUM(NFS4CLNT_DELEGRETURN);
TRACE_DEFINE_ENUM(NFS4CLNT_SESSION_RESET);
TRACE_DEFINE_ENUM(NFS4CLNT_LEASE_CONFIRM);
TRACE_DEFINE_ENUM(NFS4CLNT_SERVER_SCOPE_MISMATCH);
TRACE_DEFINE_ENUM(NFS4CLNT_PURGE_STATE);
TRACE_DEFINE_ENUM(NFS4CLNT_BIND_CONN_TO_SESSION);
TRACE_DEFINE_ENUM(NFS4CLNT_MOVED);
TRACE_DEFINE_ENUM(NFS4CLNT_LEASE_MOVED);
TRACE_DEFINE_ENUM(NFS4CLNT_DELEGATION_EXPIRED);
TRACE_DEFINE_ENUM(NFS4CLNT_RUN_MANAGER);
TRACE_DEFINE_ENUM(NFS4CLNT_RECALL_RUNNING);
TRACE_DEFINE_ENUM(NFS4CLNT_RECALL_ANY_LAYOUT_READ);
TRACE_DEFINE_ENUM(NFS4CLNT_RECALL_ANY_LAYOUT_RW);

#घोषणा show_nfs4_clp_state(state) \
	__prपूर्णांक_flags(state, "|", \
		अणु NFS4CLNT_MANAGER_RUNNING,	"MANAGER_RUNNING" पूर्ण, \
		अणु NFS4CLNT_CHECK_LEASE,		"CHECK_LEASE" पूर्ण, \
		अणु NFS4CLNT_LEASE_EXPIRED,	"LEASE_EXPIRED" पूर्ण, \
		अणु NFS4CLNT_RECLAIM_REBOOT,	"RECLAIM_REBOOT" पूर्ण, \
		अणु NFS4CLNT_RECLAIM_NOGRACE,	"RECLAIM_NOGRACE" पूर्ण, \
		अणु NFS4CLNT_DELEGRETURN,		"DELEGRETURN" पूर्ण, \
		अणु NFS4CLNT_SESSION_RESET,	"SESSION_RESET" पूर्ण, \
		अणु NFS4CLNT_LEASE_CONFIRM,	"LEASE_CONFIRM" पूर्ण, \
		अणु NFS4CLNT_SERVER_SCOPE_MISMATCH, \
						"SERVER_SCOPE_MISMATCH" पूर्ण, \
		अणु NFS4CLNT_PURGE_STATE,		"PURGE_STATE" पूर्ण, \
		अणु NFS4CLNT_BIND_CONN_TO_SESSION, \
						"BIND_CONN_TO_SESSION" पूर्ण, \
		अणु NFS4CLNT_MOVED,		"MOVED" पूर्ण, \
		अणु NFS4CLNT_LEASE_MOVED,		"LEASE_MOVED" पूर्ण, \
		अणु NFS4CLNT_DELEGATION_EXPIRED,	"DELEGATION_EXPIRED" पूर्ण, \
		अणु NFS4CLNT_RUN_MANAGER,		"RUN_MANAGER" पूर्ण, \
		अणु NFS4CLNT_RECALL_RUNNING,	"RECALL_RUNNING" पूर्ण, \
		अणु NFS4CLNT_RECALL_ANY_LAYOUT_READ, "RECALL_ANY_LAYOUT_READ" पूर्ण, \
		अणु NFS4CLNT_RECALL_ANY_LAYOUT_RW, "RECALL_ANY_LAYOUT_RW" पूर्ण)

TRACE_EVENT(nfs4_state_mgr,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp
		),

		TP_ARGS(clp),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, state)
			__string(hostname, clp->cl_hostname)
		),

		TP_fast_assign(
			__entry->state = clp->cl_state;
			__assign_str(hostname, clp->cl_hostname)
		),

		TP_prपूर्णांकk(
			"hostname=%s clp state=%s", __get_str(hostname),
			show_nfs4_clp_state(__entry->state)
		)
)

TRACE_EVENT(nfs4_state_mgr_failed,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp,
			स्थिर अक्षर *section,
			पूर्णांक status
		),

		TP_ARGS(clp, section, status),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(अचिन्हित दीर्घ, state)
			__string(hostname, clp->cl_hostname)
			__string(section, section)
		),

		TP_fast_assign(
			__entry->error = status < 0 ? -status : 0;
			__entry->state = clp->cl_state;
			__assign_str(hostname, clp->cl_hostname);
			__assign_str(section, section);
		),

		TP_prपूर्णांकk(
			"hostname=%s clp state=%s error=%ld (%s) section=%s",
			__get_str(hostname),
			show_nfs4_clp_state(__entry->state), -__entry->error,
			show_nfsv4_errors(__entry->error), __get_str(section)

		)
)

TRACE_EVENT(nfs4_xdr_bad_operation,
		TP_PROTO(
			स्थिर काष्ठा xdr_stream *xdr,
			u32 op,
			u32 expected
		),

		TP_ARGS(xdr, op, expected),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, task_id)
			__field(अचिन्हित पूर्णांक, client_id)
			__field(u32, xid)
			__field(u32, op)
			__field(u32, expected)
		),

		TP_fast_assign(
			स्थिर काष्ठा rpc_rqst *rqstp = xdr->rqst;
			स्थिर काष्ठा rpc_task *task = rqstp->rq_task;

			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client->cl_clid;
			__entry->xid = be32_to_cpu(rqstp->rq_xid);
			__entry->op = op;
			__entry->expected = expected;
		),

		TP_prपूर्णांकk(
			"task:%u@%d xid=0x%08x operation=%u, expected=%u",
			__entry->task_id, __entry->client_id, __entry->xid,
			__entry->op, __entry->expected
		)
);

DECLARE_EVENT_CLASS(nfs4_xdr_event,
		TP_PROTO(
			स्थिर काष्ठा xdr_stream *xdr,
			u32 op,
			u32 error
		),

		TP_ARGS(xdr, op, error),

		TP_STRUCT__entry(
			__field(अचिन्हित पूर्णांक, task_id)
			__field(अचिन्हित पूर्णांक, client_id)
			__field(u32, xid)
			__field(u32, op)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			स्थिर काष्ठा rpc_rqst *rqstp = xdr->rqst;
			स्थिर काष्ठा rpc_task *task = rqstp->rq_task;

			__entry->task_id = task->tk_pid;
			__entry->client_id = task->tk_client->cl_clid;
			__entry->xid = be32_to_cpu(rqstp->rq_xid);
			__entry->op = op;
			__entry->error = error;
		),

		TP_prपूर्णांकk(
			"task:%u@%d xid=0x%08x error=%ld (%s) operation=%u",
			__entry->task_id, __entry->client_id, __entry->xid,
			-__entry->error, show_nfsv4_errors(__entry->error),
			__entry->op
		)
);
#घोषणा DEFINE_NFS4_XDR_EVENT(name) \
	DEFINE_EVENT(nfs4_xdr_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा xdr_stream *xdr, \
				u32 op, \
				u32 error \
			), \
			TP_ARGS(xdr, op, error))
DEFINE_NFS4_XDR_EVENT(nfs4_xdr_status);
DEFINE_NFS4_XDR_EVENT(nfs4_xdr_bad_filehandle);

DECLARE_EVENT_CLASS(nfs4_cb_error_class,
		TP_PROTO(
			__be32 xid,
			u32 cb_ident
		),

		TP_ARGS(xid, cb_ident),

		TP_STRUCT__entry(
			__field(u32, xid)
			__field(u32, cbident)
		),

		TP_fast_assign(
			__entry->xid = be32_to_cpu(xid);
			__entry->cbident = cb_ident;
		),

		TP_prपूर्णांकk(
			"xid=0x%08x cb_ident=0x%08x",
			__entry->xid, __entry->cbident
		)
);

#घोषणा DEFINE_CB_ERROR_EVENT(name) \
	DEFINE_EVENT(nfs4_cb_error_class, nfs_cb_##name, \
			TP_PROTO( \
				__be32 xid, \
				u32 cb_ident \
			), \
			TP_ARGS(xid, cb_ident))

DEFINE_CB_ERROR_EVENT(no_clp);
DEFINE_CB_ERROR_EVENT(badprinc);

DECLARE_EVENT_CLASS(nfs4_खोलो_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_खोलो_context *ctx,
			पूर्णांक flags,
			पूर्णांक error
		),

		TP_ARGS(ctx, flags, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(अचिन्हित पूर्णांक, flags)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(u64, dir)
			__string(name, ctx->dentry->d_name.name)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__field(पूर्णांक, खोलोstateid_seq)
			__field(u32, खोलोstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा nfs4_state *state = ctx->state;
			स्थिर काष्ठा inode *inode = शून्य;

			__entry->error = -error;
			__entry->flags = flags;
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)ctx->mode;
			__entry->dev = ctx->dentry->d_sb->s_dev;
			अगर (!IS_ERR_OR_शून्य(state)) अणु
				inode = state->inode;
				__entry->stateid_seq =
					be32_to_cpu(state->stateid.seqid);
				__entry->stateid_hash =
					nfs_stateid_hash(&state->stateid);
				__entry->खोलोstateid_seq =
					be32_to_cpu(state->खोलो_stateid.seqid);
				__entry->खोलोstateid_hash =
					nfs_stateid_hash(&state->खोलो_stateid);
			पूर्ण अन्यथा अणु
				__entry->stateid_seq = 0;
				__entry->stateid_hash = 0;
				__entry->खोलोstateid_seq = 0;
				__entry->खोलोstateid_hash = 0;
			पूर्ण
			अगर (inode != शून्य) अणु
				__entry->fileid = NFS_खाताID(inode);
				__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			पूर्ण अन्यथा अणु
				__entry->fileid = 0;
				__entry->fhandle = 0;
			पूर्ण
			__entry->dir = NFS_खाताID(d_inode(ctx->dentry->d_parent));
			__assign_str(name, ctx->dentry->d_name.name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) flags=%d (%s) fmode=%s "
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"name=%02x:%02x:%llu/%s stateid=%d:0x%08x "
			"openstateid=%d:0x%08x",
			 -__entry->error,
			 show_nfsv4_errors(__entry->error),
			 __entry->flags,
			 show_खोलो_flags(__entry->flags),
			 show_भ_शेषe_flags(__entry->भ_शेषe),
			 MAJOR(__entry->dev), MINOR(__entry->dev),
			 (अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			 __entry->fhandle,
			 MAJOR(__entry->dev), MINOR(__entry->dev),
			 (अचिन्हित दीर्घ दीर्घ)__entry->dir,
			 __get_str(name),
			 __entry->stateid_seq, __entry->stateid_hash,
			 __entry->खोलोstateid_seq, __entry->खोलोstateid_hash
		)
);

#घोषणा DEFINE_NFS4_OPEN_EVENT(name) \
	DEFINE_EVENT(nfs4_खोलो_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_खोलो_context *ctx, \
				पूर्णांक flags, \
				पूर्णांक error \
			), \
			TP_ARGS(ctx, flags, error))
DEFINE_NFS4_OPEN_EVENT(nfs4_खोलो_reclaim);
DEFINE_NFS4_OPEN_EVENT(nfs4_खोलो_expired);
DEFINE_NFS4_OPEN_EVENT(nfs4_खोलो_file);

TRACE_EVENT(nfs4_cached_खोलो,
		TP_PROTO(
			स्थिर काष्ठा nfs4_state *state
		),
		TP_ARGS(state),
		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)state->state;
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_prपूर्णांकk(
			"fmode=%s fileid=%02x:%02x:%llu "
			"fhandle=0x%08x stateid=%d:0x%08x",
			__entry->भ_शेषe ?  show_भ_शेषe_flags(__entry->भ_शेषe) :
					  "closed",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

TRACE_EVENT(nfs4_बंद,
		TP_PROTO(
			स्थिर काष्ठा nfs4_state *state,
			स्थिर काष्ठा nfs_बंदargs *args,
			स्थिर काष्ठा nfs_बंदres *res,
			पूर्णांक error
		),

		TP_ARGS(state, args, res, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)state->state;
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(args->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&args->stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fmode=%s fileid=%02x:%02x:%llu "
			"fhandle=0x%08x openstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			__entry->भ_शेषe ?  show_भ_शेषe_flags(__entry->भ_शेषe) :
					  "closed",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

TRACE_DEFINE_ENUM(F_GETLK);
TRACE_DEFINE_ENUM(F_SETLK);
TRACE_DEFINE_ENUM(F_SETLKW);
TRACE_DEFINE_ENUM(F_RDLCK);
TRACE_DEFINE_ENUM(F_WRLCK);
TRACE_DEFINE_ENUM(F_UNLCK);

#घोषणा show_lock_cmd(type) \
	__prपूर्णांक_symbolic((पूर्णांक)type, \
		अणु F_GETLK, "GETLK" पूर्ण, \
		अणु F_SETLK, "SETLK" पूर्ण, \
		अणु F_SETLKW, "SETLKW" पूर्ण)
#घोषणा show_lock_type(type) \
	__prपूर्णांक_symbolic((पूर्णांक)type, \
		अणु F_RDLCK, "RDLCK" पूर्ण, \
		अणु F_WRLCK, "WRLCK" पूर्ण, \
		अणु F_UNLCK, "UNLCK" पूर्ण)

DECLARE_EVENT_CLASS(nfs4_lock_event,
		TP_PROTO(
			स्थिर काष्ठा file_lock *request,
			स्थिर काष्ठा nfs4_state *state,
			पूर्णांक cmd,
			पूर्णांक error
		),

		TP_ARGS(request, state, cmd, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, cmd)
			__field(अक्षर, type)
			__field(loff_t, start)
			__field(loff_t, end)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->error = error < 0 ? -error : 0;
			__entry->cmd = cmd;
			__entry->type = request->fl_type;
			__entry->start = request->fl_start;
			__entry->end = request->fl_end;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) cmd=%s:%s range=%lld:%lld "
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			show_lock_cmd(__entry->cmd),
			show_lock_type(__entry->type),
			(दीर्घ दीर्घ)__entry->start,
			(दीर्घ दीर्घ)__entry->end,
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

#घोषणा DEFINE_NFS4_LOCK_EVENT(name) \
	DEFINE_EVENT(nfs4_lock_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा file_lock *request, \
				स्थिर काष्ठा nfs4_state *state, \
				पूर्णांक cmd, \
				पूर्णांक error \
			), \
			TP_ARGS(request, state, cmd, error))
DEFINE_NFS4_LOCK_EVENT(nfs4_get_lock);
DEFINE_NFS4_LOCK_EVENT(nfs4_unlock);

TRACE_EVENT(nfs4_set_lock,
		TP_PROTO(
			स्थिर काष्ठा file_lock *request,
			स्थिर काष्ठा nfs4_state *state,
			स्थिर nfs4_stateid *lockstateid,
			पूर्णांक cmd,
			पूर्णांक error
		),

		TP_ARGS(request, state, lockstateid, cmd, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, cmd)
			__field(अक्षर, type)
			__field(loff_t, start)
			__field(loff_t, end)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__field(पूर्णांक, lockstateid_seq)
			__field(u32, lockstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->error = error < 0 ? -error : 0;
			__entry->cmd = cmd;
			__entry->type = request->fl_type;
			__entry->start = request->fl_start;
			__entry->end = request->fl_end;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entry->lockstateid_seq =
				be32_to_cpu(lockstateid->seqid);
			__entry->lockstateid_hash =
				nfs_stateid_hash(lockstateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) cmd=%s:%s range=%lld:%lld "
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x lockstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			show_lock_cmd(__entry->cmd),
			show_lock_type(__entry->type),
			(दीर्घ दीर्घ)__entry->start,
			(दीर्घ दीर्घ)__entry->end,
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash,
			__entry->lockstateid_seq, __entry->lockstateid_hash
		)
);

TRACE_DEFINE_ENUM(LK_STATE_IN_USE);
TRACE_DEFINE_ENUM(NFS_DELEGATED_STATE);
TRACE_DEFINE_ENUM(NFS_OPEN_STATE);
TRACE_DEFINE_ENUM(NFS_O_RDONLY_STATE);
TRACE_DEFINE_ENUM(NFS_O_WRONLY_STATE);
TRACE_DEFINE_ENUM(NFS_O_RDWR_STATE);
TRACE_DEFINE_ENUM(NFS_STATE_RECLAIM_REBOOT);
TRACE_DEFINE_ENUM(NFS_STATE_RECLAIM_NOGRACE);
TRACE_DEFINE_ENUM(NFS_STATE_POSIX_LOCKS);
TRACE_DEFINE_ENUM(NFS_STATE_RECOVERY_FAILED);
TRACE_DEFINE_ENUM(NFS_STATE_MAY_NOTIFY_LOCK);
TRACE_DEFINE_ENUM(NFS_STATE_CHANGE_WAIT);
TRACE_DEFINE_ENUM(NFS_CLNT_DST_SSC_COPY_STATE);
TRACE_DEFINE_ENUM(NFS_CLNT_SRC_SSC_COPY_STATE);
TRACE_DEFINE_ENUM(NFS_SRV_SSC_COPY_STATE);

#घोषणा show_nfs4_state_flags(flags) \
	__prपूर्णांक_flags(flags, "|", \
		अणु LK_STATE_IN_USE,		"IN_USE" पूर्ण, \
		अणु NFS_DELEGATED_STATE,		"DELEGATED" पूर्ण, \
		अणु NFS_OPEN_STATE,		"OPEN" पूर्ण, \
		अणु NFS_O_RDONLY_STATE,		"O_RDONLY" पूर्ण, \
		अणु NFS_O_WRONLY_STATE,		"O_WRONLY" पूर्ण, \
		अणु NFS_O_RDWR_STATE,		"O_RDWR" पूर्ण, \
		अणु NFS_STATE_RECLAIM_REBOOT,	"RECLAIM_REBOOT" पूर्ण, \
		अणु NFS_STATE_RECLAIM_NOGRACE,	"RECLAIM_NOGRACE" पूर्ण, \
		अणु NFS_STATE_POSIX_LOCKS,	"POSIX_LOCKS" पूर्ण, \
		अणु NFS_STATE_RECOVERY_FAILED,	"RECOVERY_FAILED" पूर्ण, \
		अणु NFS_STATE_MAY_NOTIFY_LOCK,	"MAY_NOTIFY_LOCK" पूर्ण, \
		अणु NFS_STATE_CHANGE_WAIT,	"CHANGE_WAIT" पूर्ण, \
		अणु NFS_CLNT_DST_SSC_COPY_STATE,	"CLNT_DST_SSC_COPY" पूर्ण, \
		अणु NFS_CLNT_SRC_SSC_COPY_STATE,	"CLNT_SRC_SSC_COPY" पूर्ण, \
		अणु NFS_SRV_SSC_COPY_STATE,	"SRV_SSC_COPY" पूर्ण)

#घोषणा show_nfs4_lock_flags(flags) \
	__prपूर्णांक_flags(flags, "|", \
		अणु BIT(NFS_LOCK_INITIALIZED),	"INITIALIZED" पूर्ण, \
		अणु BIT(NFS_LOCK_LOST),		"LOST" पूर्ण)

TRACE_EVENT(nfs4_state_lock_reclaim,
		TP_PROTO(
			स्थिर काष्ठा nfs4_state *state,
			स्थिर काष्ठा nfs4_lock_state *lock
		),

		TP_ARGS(state, lock),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित दीर्घ, state_flags)
			__field(अचिन्हित दीर्घ, lock_flags)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->state_flags = state->flags;
			__entry->lock_flags = lock->ls_flags;
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x state_flags=%s lock_flags=%s",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid, __entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash,
			show_nfs4_state_flags(__entry->state_flags),
			show_nfs4_lock_flags(__entry->lock_flags)
		)
)

DECLARE_EVENT_CLASS(nfs4_set_delegation_event,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			भ_शेषe_t भ_शेषe
		),

		TP_ARGS(inode, भ_शेषe),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित पूर्णांक, भ_शेषe)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->भ_शेषe = (__क्रमce अचिन्हित पूर्णांक)भ_शेषe;
		),

		TP_prपूर्णांकk(
			"fmode=%s fileid=%02x:%02x:%llu fhandle=0x%08x",
			show_भ_शेषe_flags(__entry->भ_शेषe),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle
		)
);
#घोषणा DEFINE_NFS4_SET_DELEGATION_EVENT(name) \
	DEFINE_EVENT(nfs4_set_delegation_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *inode, \
				भ_शेषe_t भ_शेषe \
			), \
			TP_ARGS(inode, भ_शेषe))
DEFINE_NFS4_SET_DELEGATION_EVENT(nfs4_set_delegation);
DEFINE_NFS4_SET_DELEGATION_EVENT(nfs4_reclaim_delegation);

TRACE_EVENT(nfs4_delegवापस_निकास,
		TP_PROTO(
			स्थिर काष्ठा nfs4_delegवापसargs *args,
			स्थिर काष्ठा nfs4_delegवापसres *res,
			पूर्णांक error
		),

		TP_ARGS(args, res, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			__entry->dev = res->server->s_dev;
			__entry->fhandle = nfs_fhandle_hash(args->fhandle);
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(args->stateid->seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(args->stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) dev=%02x:%02x fhandle=0x%08x "
			"stateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

#अगर_घोषित CONFIG_NFS_V4_1
DECLARE_EVENT_CLASS(nfs4_test_stateid_event,
		TP_PROTO(
			स्थिर काष्ठा nfs4_state *state,
			स्थिर काष्ठा nfs4_lock_state *lsp,
			पूर्णांक error
		),

		TP_ARGS(state, lsp, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = state->inode;

			__entry->error = error < 0 ? -error : 0;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

#घोषणा DEFINE_NFS4_TEST_STATEID_EVENT(name) \
	DEFINE_EVENT(nfs4_test_stateid_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs4_state *state, \
				स्थिर काष्ठा nfs4_lock_state *lsp, \
				पूर्णांक error \
			), \
			TP_ARGS(state, lsp, error))
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_delegation_stateid);
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_खोलो_stateid);
DEFINE_NFS4_TEST_STATEID_EVENT(nfs4_test_lock_stateid);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

DECLARE_EVENT_CLASS(nfs4_lookup_event,
		TP_PROTO(
			स्थिर काष्ठा inode *dir,
			स्थिर काष्ठा qstr *name,
			पूर्णांक error
		),

		TP_ARGS(dir, name, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(अचिन्हित दीर्घ, error)
			__field(u64, dir)
			__string(name, name->name)
		),

		TP_fast_assign(
			__entry->dev = dir->i_sb->s_dev;
			__entry->dir = NFS_खाताID(dir);
			__entry->error = -error;
			__assign_str(name, name->name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) name=%02x:%02x:%llu/%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->dir,
			__get_str(name)
		)
);

#घोषणा DEFINE_NFS4_LOOKUP_EVENT(name) \
	DEFINE_EVENT(nfs4_lookup_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *dir, \
				स्थिर काष्ठा qstr *name, \
				पूर्णांक error \
			), \
			TP_ARGS(dir, name, error))

DEFINE_NFS4_LOOKUP_EVENT(nfs4_lookup);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_symlink);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_सूची_गढ़ो);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_mknod);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_हटाओ);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_get_fs_locations);
DEFINE_NFS4_LOOKUP_EVENT(nfs4_secinfo);

TRACE_EVENT(nfs4_lookupp,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			पूर्णांक error
		),

		TP_ARGS(inode, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, ino)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->ino = NFS_खाताID(inode);
			__entry->error = error < 0 ? -error : 0;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) inode=%02x:%02x:%llu",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->ino
		)
);

TRACE_EVENT(nfs4_नाम,
		TP_PROTO(
			स्थिर काष्ठा inode *olddir,
			स्थिर काष्ठा qstr *oldname,
			स्थिर काष्ठा inode *newdir,
			स्थिर काष्ठा qstr *newname,
			पूर्णांक error
		),

		TP_ARGS(olddir, oldname, newdir, newname, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(अचिन्हित दीर्घ, error)
			__field(u64, olddir)
			__string(oldname, oldname->name)
			__field(u64, newdir)
			__string(newname, newname->name)
		),

		TP_fast_assign(
			__entry->dev = olddir->i_sb->s_dev;
			__entry->olddir = NFS_खाताID(olddir);
			__entry->newdir = NFS_खाताID(newdir);
			__entry->error = error < 0 ? -error : 0;
			__assign_str(oldname, oldname->name);
			__assign_str(newname, newname->name);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) oldname=%02x:%02x:%llu/%s "
			"newname=%02x:%02x:%llu/%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->olddir,
			__get_str(oldname),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->newdir,
			__get_str(newname)
		)
);

DECLARE_EVENT_CLASS(nfs4_inode_event,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			पूर्णांक error
		),

		TP_ARGS(inode, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->error = error < 0 ? -error : 0;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle
		)
);

#घोषणा DEFINE_NFS4_INODE_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *inode, \
				पूर्णांक error \
			), \
			TP_ARGS(inode, error))

DEFINE_NFS4_INODE_EVENT(nfs4_access);
DEFINE_NFS4_INODE_EVENT(nfs4_पढ़ोlink);
DEFINE_NFS4_INODE_EVENT(nfs4_सूची_पढ़ो);
DEFINE_NFS4_INODE_EVENT(nfs4_get_acl);
DEFINE_NFS4_INODE_EVENT(nfs4_set_acl);
#अगर_घोषित CONFIG_NFS_V4_SECURITY_LABEL
DEFINE_NFS4_INODE_EVENT(nfs4_get_security_label);
DEFINE_NFS4_INODE_EVENT(nfs4_set_security_label);
#पूर्ण_अगर /* CONFIG_NFS_V4_SECURITY_LABEL */

DECLARE_EVENT_CLASS(nfs4_inode_stateid_event,
		TP_PROTO(
			स्थिर काष्ठा inode *inode,
			स्थिर nfs4_stateid *stateid,
			पूर्णांक error
		),

		TP_ARGS(inode, stateid, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(stateid->seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash
		)
);

#घोषणा DEFINE_NFS4_INODE_STATEID_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_stateid_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा inode *inode, \
				स्थिर nfs4_stateid *stateid, \
				पूर्णांक error \
			), \
			TP_ARGS(inode, stateid, error))

DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_setattr);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_delegवापस);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_खोलो_stateid_update);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_खोलो_stateid_update_रुको);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_बंद_stateid_update_रुको);

DECLARE_EVENT_CLASS(nfs4_getattr_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_server *server,
			स्थिर काष्ठा nfs_fh *fhandle,
			स्थिर काष्ठा nfs_fattr *fattr,
			पूर्णांक error
		),

		TP_ARGS(server, fhandle, fattr, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित पूर्णांक, valid)
			__field(अचिन्हित दीर्घ, error)
		),

		TP_fast_assign(
			__entry->dev = server->s_dev;
			__entry->valid = fattr->valid;
			__entry->fhandle = nfs_fhandle_hash(fhandle);
			__entry->fileid = (fattr->valid & NFS_ATTR_FATTR_खाताID) ? fattr->fileid : 0;
			__entry->error = error < 0 ? -error : 0;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"valid=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			show_nfs_fattr_flags(__entry->valid)
		)
);

#घोषणा DEFINE_NFS4_GETATTR_EVENT(name) \
	DEFINE_EVENT(nfs4_getattr_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_server *server, \
				स्थिर काष्ठा nfs_fh *fhandle, \
				स्थिर काष्ठा nfs_fattr *fattr, \
				पूर्णांक error \
			), \
			TP_ARGS(server, fhandle, fattr, error))
DEFINE_NFS4_GETATTR_EVENT(nfs4_getattr);
DEFINE_NFS4_GETATTR_EVENT(nfs4_lookup_root);
DEFINE_NFS4_GETATTR_EVENT(nfs4_fsinfo);

DECLARE_EVENT_CLASS(nfs4_inode_callback_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp,
			स्थिर काष्ठा nfs_fh *fhandle,
			स्थिर काष्ठा inode *inode,
			पूर्णांक error
		),

		TP_ARGS(clp, fhandle, inode, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__string(dstaddr, clp ? clp->cl_hostname : "unknown")
		),

		TP_fast_assign(
			__entry->error = error < 0 ? -error : 0;
			__entry->fhandle = nfs_fhandle_hash(fhandle);
			अगर (!IS_ERR_OR_शून्य(inode)) अणु
				__entry->fileid = NFS_खाताID(inode);
				__entry->dev = inode->i_sb->s_dev;
			पूर्ण अन्यथा अणु
				__entry->fileid = 0;
				__entry->dev = 0;
			पूर्ण
			__assign_str(dstaddr, clp ? clp->cl_hostname : "unknown")
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"dstaddr=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__get_str(dstaddr)
		)
);

#घोषणा DEFINE_NFS4_INODE_CALLBACK_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_callback_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_client *clp, \
				स्थिर काष्ठा nfs_fh *fhandle, \
				स्थिर काष्ठा inode *inode, \
				पूर्णांक error \
			), \
			TP_ARGS(clp, fhandle, inode, error))
DEFINE_NFS4_INODE_CALLBACK_EVENT(nfs4_cb_getattr);

DECLARE_EVENT_CLASS(nfs4_inode_stateid_callback_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp,
			स्थिर काष्ठा nfs_fh *fhandle,
			स्थिर काष्ठा inode *inode,
			स्थिर nfs4_stateid *stateid,
			पूर्णांक error
		),

		TP_ARGS(clp, fhandle, inode, stateid, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__string(dstaddr, clp ? clp->cl_hostname : "unknown")
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
		),

		TP_fast_assign(
			__entry->error = error < 0 ? -error : 0;
			__entry->fhandle = nfs_fhandle_hash(fhandle);
			अगर (!IS_ERR_OR_शून्य(inode)) अणु
				__entry->fileid = NFS_खाताID(inode);
				__entry->dev = inode->i_sb->s_dev;
			पूर्ण अन्यथा अणु
				__entry->fileid = 0;
				__entry->dev = 0;
			पूर्ण
			__assign_str(dstaddr, clp ? clp->cl_hostname : "unknown")
			__entry->stateid_seq =
				be32_to_cpu(stateid->seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(stateid);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"stateid=%d:0x%08x dstaddr=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->stateid_seq, __entry->stateid_hash,
			__get_str(dstaddr)
		)
);

#घोषणा DEFINE_NFS4_INODE_STATEID_CALLBACK_EVENT(name) \
	DEFINE_EVENT(nfs4_inode_stateid_callback_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_client *clp, \
				स्थिर काष्ठा nfs_fh *fhandle, \
				स्थिर काष्ठा inode *inode, \
				स्थिर nfs4_stateid *stateid, \
				पूर्णांक error \
			), \
			TP_ARGS(clp, fhandle, inode, stateid, error))
DEFINE_NFS4_INODE_STATEID_CALLBACK_EVENT(nfs4_cb_recall);
DEFINE_NFS4_INODE_STATEID_CALLBACK_EVENT(nfs4_cb_layoutrecall_file);

DECLARE_EVENT_CLASS(nfs4_idmap_event,
		TP_PROTO(
			स्थिर अक्षर *name,
			पूर्णांक len,
			u32 id,
			पूर्णांक error
		),

		TP_ARGS(name, len, id, error),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(u32, id)
			__dynamic_array(अक्षर, name, len > 0 ? len + 1 : 1)
		),

		TP_fast_assign(
			अगर (len < 0)
				len = 0;
			__entry->error = error < 0 ? error : 0;
			__entry->id = id;
			स_नकल(__get_str(name), name, len);
			__get_str(name)[len] = 0;
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) id=%u name=%s",
			-__entry->error, show_nfsv4_errors(__entry->error),
			__entry->id,
			__get_str(name)
		)
);
#घोषणा DEFINE_NFS4_IDMAP_EVENT(name) \
	DEFINE_EVENT(nfs4_idmap_event, name, \
			TP_PROTO( \
				स्थिर अक्षर *name, \
				पूर्णांक len, \
				u32 id, \
				पूर्णांक error \
			), \
			TP_ARGS(name, len, id, error))
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_name_to_uid);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_group_to_gid);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_uid_to_name);
DEFINE_NFS4_IDMAP_EVENT(nfs4_map_gid_to_group);

#अगर_घोषित CONFIG_NFS_V4_1
#घोषणा NFS4_LSEG_LAYOUT_STATEID_HASH(lseg) \
	(lseg ? nfs_stateid_hash(&lseg->pls_layout->plh_stateid) : 0)
#अन्यथा
#घोषणा NFS4_LSEG_LAYOUT_STATEID_HASH(lseg) (0)
#पूर्ण_अगर

DECLARE_EVENT_CLASS(nfs4_पढ़ो_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_pgio_header *hdr,
			पूर्णांक error
		),

		TP_ARGS(hdr, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, arg_count)
			__field(u32, res_count)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;
			स्थिर काष्ठा nfs4_state *state =
				hdr->args.context->state;
			स्थिर काष्ठा pnfs_layout_segment *lseg = hdr->lseg;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
			__entry->offset = hdr->args.offset;
			__entry->arg_count = hdr->args.count;
			__entry->res_count = hdr->res.count;
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entry->layoutstateid_seq = lseg ? lseg->pls_seq : 0;
			__entry->layoutstateid_hash =
				NFS4_LSEG_LAYOUT_STATEID_HASH(lseg);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u res=%u stateid=%d:0x%08x "
			"layoutstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset,
			__entry->arg_count, __entry->res_count,
			__entry->stateid_seq, __entry->stateid_hash,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash
		)
);
#घोषणा DEFINE_NFS4_READ_EVENT(name) \
	DEFINE_EVENT(nfs4_पढ़ो_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_pgio_header *hdr, \
				पूर्णांक error \
			), \
			TP_ARGS(hdr, error))
DEFINE_NFS4_READ_EVENT(nfs4_पढ़ो);
#अगर_घोषित CONFIG_NFS_V4_1
DEFINE_NFS4_READ_EVENT(nfs4_pnfs_पढ़ो);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

DECLARE_EVENT_CLASS(nfs4_ग_लिखो_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_pgio_header *hdr,
			पूर्णांक error
		),

		TP_ARGS(hdr, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, arg_count)
			__field(u32, res_count)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = hdr->args.fh ?
						  hdr->args.fh : &nfsi->fh;
			स्थिर काष्ठा nfs4_state *state =
				hdr->args.context->state;
			स्थिर काष्ठा pnfs_layout_segment *lseg = hdr->lseg;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
			__entry->offset = hdr->args.offset;
			__entry->arg_count = hdr->args.count;
			__entry->res_count = hdr->res.count;
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			__entry->layoutstateid_seq = lseg ? lseg->pls_seq : 0;
			__entry->layoutstateid_hash =
				NFS4_LSEG_LAYOUT_STATEID_HASH(lseg);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u res=%u stateid=%d:0x%08x "
			"layoutstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset,
			__entry->arg_count, __entry->res_count,
			__entry->stateid_seq, __entry->stateid_hash,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash
		)
);

#घोषणा DEFINE_NFS4_WRITE_EVENT(name) \
	DEFINE_EVENT(nfs4_ग_लिखो_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_pgio_header *hdr, \
				पूर्णांक error \
			), \
			TP_ARGS(hdr, error))
DEFINE_NFS4_WRITE_EVENT(nfs4_ग_लिखो);
#अगर_घोषित CONFIG_NFS_V4_1
DEFINE_NFS4_WRITE_EVENT(nfs4_pnfs_ग_लिखो);
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

DECLARE_EVENT_CLASS(nfs4_commit_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_commit_data *data,
			पूर्णांक error
		),

		TP_ARGS(data, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(अचिन्हित दीर्घ, error)
			__field(loff_t, offset)
			__field(u32, count)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = data->inode;
			स्थिर काष्ठा nfs_inode *nfsi = NFS_I(inode);
			स्थिर काष्ठा nfs_fh *fh = data->args.fh ?
						  data->args.fh : &nfsi->fh;
			स्थिर काष्ठा pnfs_layout_segment *lseg = data->lseg;

			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = nfsi->fileid;
			__entry->fhandle = nfs_fhandle_hash(fh);
			__entry->offset = data->args.offset;
			__entry->count = data->args.count;
			__entry->error = error < 0 ? -error : 0;
			__entry->layoutstateid_seq = lseg ? lseg->pls_seq : 0;
			__entry->layoutstateid_hash =
				NFS4_LSEG_LAYOUT_STATEID_HASH(lseg);
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%lld count=%u layoutstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			(दीर्घ दीर्घ)__entry->offset,
			__entry->count,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash
		)
);
#घोषणा DEFINE_NFS4_COMMIT_EVENT(name) \
	DEFINE_EVENT(nfs4_commit_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_commit_data *data, \
				पूर्णांक error \
			), \
			TP_ARGS(data, error))
DEFINE_NFS4_COMMIT_EVENT(nfs4_commit);
#अगर_घोषित CONFIG_NFS_V4_1
DEFINE_NFS4_COMMIT_EVENT(nfs4_pnfs_commit_ds);

TRACE_DEFINE_ENUM(IOMODE_READ);
TRACE_DEFINE_ENUM(IOMODE_RW);
TRACE_DEFINE_ENUM(IOMODE_ANY);

#घोषणा show_pnfs_iomode(iomode) \
	__prपूर्णांक_symbolic(iomode, \
		अणु IOMODE_READ, "READ" पूर्ण, \
		अणु IOMODE_RW, "RW" पूर्ण, \
		अणु IOMODE_ANY, "ANY" पूर्ण)

TRACE_EVENT(nfs4_layoutget,
		TP_PROTO(
			स्थिर काष्ठा nfs_खोलो_context *ctx,
			स्थिर काष्ठा pnfs_layout_range *args,
			स्थिर काष्ठा pnfs_layout_range *res,
			स्थिर nfs4_stateid *layout_stateid,
			पूर्णांक error
		),

		TP_ARGS(ctx, args, res, layout_stateid, error),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(u32, iomode)
			__field(u64, offset)
			__field(u64, count)
			__field(अचिन्हित दीर्घ, error)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = d_inode(ctx->dentry);
			स्थिर काष्ठा nfs4_state *state = ctx->state;
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->iomode = args->iomode;
			__entry->offset = args->offset;
			__entry->count = args->length;
			__entry->error = error < 0 ? -error : 0;
			__entry->stateid_seq =
				be32_to_cpu(state->stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&state->stateid);
			अगर (!error) अणु
				__entry->layoutstateid_seq =
				be32_to_cpu(layout_stateid->seqid);
				__entry->layoutstateid_hash =
				nfs_stateid_hash(layout_stateid);
			पूर्ण अन्यथा अणु
				__entry->layoutstateid_seq = 0;
				__entry->layoutstateid_hash = 0;
			पूर्ण
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"iomode=%s offset=%llu count=%llu stateid=%d:0x%08x "
			"layoutstateid=%d:0x%08x",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			show_pnfs_iomode(__entry->iomode),
			(अचिन्हित दीर्घ दीर्घ)__entry->offset,
			(अचिन्हित दीर्घ दीर्घ)__entry->count,
			__entry->stateid_seq, __entry->stateid_hash,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash
		)
);

DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_layoutcommit);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_layoutवापस);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_layoutवापस_on_बंद);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_layouterror);
DEFINE_NFS4_INODE_STATEID_EVENT(nfs4_layoutstats);

TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_UNKNOWN);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_NO_PNFS);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_RD_ZEROLEN);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_MDSTHRESH);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_NOMEM);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_BULK_RECALL);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_IO_TEST_FAIL);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_FOUND_CACHED);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_RETURN);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_BLOCKED);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_INVALID_OPEN);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_RETRY);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_SEND_LAYOUTGET);
TRACE_DEFINE_ENUM(PNFS_UPDATE_LAYOUT_EXIT);

#घोषणा show_pnfs_update_layout_reason(reason)				\
	__prपूर्णांक_symbolic(reason,					\
		अणु PNFS_UPDATE_LAYOUT_UNKNOWN, "unknown" पूर्ण,		\
		अणु PNFS_UPDATE_LAYOUT_NO_PNFS, "no pnfs" पूर्ण,		\
		अणु PNFS_UPDATE_LAYOUT_RD_ZEROLEN, "read+zerolen" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_MDSTHRESH, "mdsthresh" पूर्ण,		\
		अणु PNFS_UPDATE_LAYOUT_NOMEM, "nomem" पूर्ण,			\
		अणु PNFS_UPDATE_LAYOUT_BULK_RECALL, "bulk recall" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_IO_TEST_FAIL, "io test fail" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_FOUND_CACHED, "found cached" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_RETURN, "layoutreturn" पूर्ण,		\
		अणु PNFS_UPDATE_LAYOUT_BLOCKED, "layouts blocked" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_INVALID_OPEN, "invalid open" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_RETRY, "retrying" पूर्ण,	\
		अणु PNFS_UPDATE_LAYOUT_SEND_LAYOUTGET, "sent layoutget" पूर्ण, \
		अणु PNFS_UPDATE_LAYOUT_EXIT, "exit" पूर्ण)

TRACE_EVENT(pnfs_update_layout,
		TP_PROTO(काष्ठा inode *inode,
			loff_t pos,
			u64 count,
			क्रमागत pnfs_iomode iomode,
			काष्ठा pnfs_layout_hdr *lo,
			काष्ठा pnfs_layout_segment *lseg,
			क्रमागत pnfs_update_layout_reason reason
		),
		TP_ARGS(inode, pos, count, iomode, lo, lseg, reason),
		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, fileid)
			__field(u32, fhandle)
			__field(loff_t, pos)
			__field(u64, count)
			__field(क्रमागत pnfs_iomode, iomode)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
			__field(दीर्घ, lseg)
			__field(क्रमागत pnfs_update_layout_reason, reason)
		),
		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->pos = pos;
			__entry->count = count;
			__entry->iomode = iomode;
			__entry->reason = reason;
			अगर (lo != शून्य) अणु
				__entry->layoutstateid_seq =
				be32_to_cpu(lo->plh_stateid.seqid);
				__entry->layoutstateid_hash =
				nfs_stateid_hash(&lo->plh_stateid);
			पूर्ण अन्यथा अणु
				__entry->layoutstateid_seq = 0;
				__entry->layoutstateid_hash = 0;
			पूर्ण
			__entry->lseg = (दीर्घ)lseg;
		),
		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"iomode=%s pos=%llu count=%llu "
			"layoutstateid=%d:0x%08x lseg=0x%lx (%s)",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			show_pnfs_iomode(__entry->iomode),
			(अचिन्हित दीर्घ दीर्घ)__entry->pos,
			(अचिन्हित दीर्घ दीर्घ)__entry->count,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash,
			__entry->lseg,
			show_pnfs_update_layout_reason(__entry->reason)
		)
);

DECLARE_EVENT_CLASS(pnfs_layout_event,
		TP_PROTO(काष्ठा inode *inode,
			loff_t pos,
			u64 count,
			क्रमागत pnfs_iomode iomode,
			काष्ठा pnfs_layout_hdr *lo,
			काष्ठा pnfs_layout_segment *lseg
		),
		TP_ARGS(inode, pos, count, iomode, lo, lseg),
		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(u64, fileid)
			__field(u32, fhandle)
			__field(loff_t, pos)
			__field(u64, count)
			__field(क्रमागत pnfs_iomode, iomode)
			__field(पूर्णांक, layoutstateid_seq)
			__field(u32, layoutstateid_hash)
			__field(दीर्घ, lseg)
		),
		TP_fast_assign(
			__entry->dev = inode->i_sb->s_dev;
			__entry->fileid = NFS_खाताID(inode);
			__entry->fhandle = nfs_fhandle_hash(NFS_FH(inode));
			__entry->pos = pos;
			__entry->count = count;
			__entry->iomode = iomode;
			अगर (lo != शून्य) अणु
				__entry->layoutstateid_seq =
				be32_to_cpu(lo->plh_stateid.seqid);
				__entry->layoutstateid_hash =
				nfs_stateid_hash(&lo->plh_stateid);
			पूर्ण अन्यथा अणु
				__entry->layoutstateid_seq = 0;
				__entry->layoutstateid_hash = 0;
			पूर्ण
			__entry->lseg = (दीर्घ)lseg;
		),
		TP_prपूर्णांकk(
			"fileid=%02x:%02x:%llu fhandle=0x%08x "
			"iomode=%s pos=%llu count=%llu "
			"layoutstateid=%d:0x%08x lseg=0x%lx",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			show_pnfs_iomode(__entry->iomode),
			(अचिन्हित दीर्घ दीर्घ)__entry->pos,
			(अचिन्हित दीर्घ दीर्घ)__entry->count,
			__entry->layoutstateid_seq, __entry->layoutstateid_hash,
			__entry->lseg
		)
);

#घोषणा DEFINE_PNFS_LAYOUT_EVENT(name) \
	DEFINE_EVENT(pnfs_layout_event, name, \
		TP_PROTO(काष्ठा inode *inode, \
			loff_t pos, \
			u64 count, \
			क्रमागत pnfs_iomode iomode, \
			काष्ठा pnfs_layout_hdr *lo, \
			काष्ठा pnfs_layout_segment *lseg \
		), \
		TP_ARGS(inode, pos, count, iomode, lo, lseg))

DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_pg_init_पढ़ो);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_pg_init_ग_लिखो);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_pg_get_mirror_count);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_पढ़ो_करोne);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_ग_लिखो_करोne);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_पढ़ो_pagelist);
DEFINE_PNFS_LAYOUT_EVENT(pnfs_mds_fallback_ग_लिखो_pagelist);

DECLARE_EVENT_CLASS(nfs4_deviceid_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_client *clp,
			स्थिर काष्ठा nfs4_deviceid *deviceid
		),

		TP_ARGS(clp, deviceid),

		TP_STRUCT__entry(
			__string(dstaddr, clp->cl_hostname)
			__array(अचिन्हित अक्षर, deviceid, NFS4_DEVICEID4_SIZE)
		),

		TP_fast_assign(
			__assign_str(dstaddr, clp->cl_hostname);
			स_नकल(__entry->deviceid, deviceid->data,
			       NFS4_DEVICEID4_SIZE);
		),

		TP_prपूर्णांकk(
			"deviceid=%s, dstaddr=%s",
			__prपूर्णांक_hex(__entry->deviceid, NFS4_DEVICEID4_SIZE),
			__get_str(dstaddr)
		)
);
#घोषणा DEFINE_PNFS_DEVICEID_EVENT(name) \
	DEFINE_EVENT(nfs4_deviceid_event, name, \
			TP_PROTO(स्थिर काष्ठा nfs_client *clp, \
				स्थिर काष्ठा nfs4_deviceid *deviceid \
			), \
			TP_ARGS(clp, deviceid))
DEFINE_PNFS_DEVICEID_EVENT(nfs4_deviceid_मुक्त);

DECLARE_EVENT_CLASS(nfs4_deviceid_status,
		TP_PROTO(
			स्थिर काष्ठा nfs_server *server,
			स्थिर काष्ठा nfs4_deviceid *deviceid,
			पूर्णांक status
		),

		TP_ARGS(server, deviceid, status),

		TP_STRUCT__entry(
			__field(dev_t, dev)
			__field(पूर्णांक, status)
			__string(dstaddr, server->nfs_client->cl_hostname)
			__array(अचिन्हित अक्षर, deviceid, NFS4_DEVICEID4_SIZE)
		),

		TP_fast_assign(
			__entry->dev = server->s_dev;
			__entry->status = status;
			__assign_str(dstaddr, server->nfs_client->cl_hostname);
			स_नकल(__entry->deviceid, deviceid->data,
			       NFS4_DEVICEID4_SIZE);
		),

		TP_prपूर्णांकk(
			"dev=%02x:%02x: deviceid=%s, dstaddr=%s, status=%d",
			MAJOR(__entry->dev), MINOR(__entry->dev),
			__prपूर्णांक_hex(__entry->deviceid, NFS4_DEVICEID4_SIZE),
			__get_str(dstaddr),
			__entry->status
		)
);
#घोषणा DEFINE_PNFS_DEVICEID_STATUS(name) \
	DEFINE_EVENT(nfs4_deviceid_status, name, \
			TP_PROTO(स्थिर काष्ठा nfs_server *server, \
				स्थिर काष्ठा nfs4_deviceid *deviceid, \
				पूर्णांक status \
			), \
			TP_ARGS(server, deviceid, status))
DEFINE_PNFS_DEVICEID_STATUS(nfs4_getdeviceinfo);
DEFINE_PNFS_DEVICEID_STATUS(nfs4_find_deviceid);

DECLARE_EVENT_CLASS(nfs4_flexfiles_io_event,
		TP_PROTO(
			स्थिर काष्ठा nfs_pgio_header *hdr
		),

		TP_ARGS(hdr),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, count)
			__field(पूर्णांक, stateid_seq)
			__field(u32, stateid_hash)
			__string(dstaddr, hdr->ds_clp ?
				rpc_peeraddr2str(hdr->ds_clp->cl_rpcclient,
					RPC_DISPLAY_ADDR) : "unknown")
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = hdr->inode;

			__entry->error = hdr->res.op_status;
			__entry->fhandle = nfs_fhandle_hash(hdr->args.fh);
			__entry->fileid = NFS_खाताID(inode);
			__entry->dev = inode->i_sb->s_dev;
			__entry->offset = hdr->args.offset;
			__entry->count = hdr->args.count;
			__entry->stateid_seq =
				be32_to_cpu(hdr->args.stateid.seqid);
			__entry->stateid_hash =
				nfs_stateid_hash(&hdr->args.stateid);
			__assign_str(dstaddr, hdr->ds_clp ?
				rpc_peeraddr2str(hdr->ds_clp->cl_rpcclient,
					RPC_DISPLAY_ADDR) : "unknown");
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%llu count=%u stateid=%d:0x%08x dstaddr=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->offset, __entry->count,
			__entry->stateid_seq, __entry->stateid_hash,
			__get_str(dstaddr)
		)
);

#घोषणा DEFINE_NFS4_FLEXखाताS_IO_EVENT(name) \
	DEFINE_EVENT(nfs4_flexfiles_io_event, name, \
			TP_PROTO( \
				स्थिर काष्ठा nfs_pgio_header *hdr \
			), \
			TP_ARGS(hdr))
DEFINE_NFS4_FLEXखाताS_IO_EVENT(ff_layout_पढ़ो_error);
DEFINE_NFS4_FLEXखाताS_IO_EVENT(ff_layout_ग_लिखो_error);

TRACE_EVENT(ff_layout_commit_error,
		TP_PROTO(
			स्थिर काष्ठा nfs_commit_data *data
		),

		TP_ARGS(data),

		TP_STRUCT__entry(
			__field(अचिन्हित दीर्घ, error)
			__field(dev_t, dev)
			__field(u32, fhandle)
			__field(u64, fileid)
			__field(loff_t, offset)
			__field(u32, count)
			__string(dstaddr, data->ds_clp ?
				rpc_peeraddr2str(data->ds_clp->cl_rpcclient,
					RPC_DISPLAY_ADDR) : "unknown")
		),

		TP_fast_assign(
			स्थिर काष्ठा inode *inode = data->inode;

			__entry->error = data->res.op_status;
			__entry->fhandle = nfs_fhandle_hash(data->args.fh);
			__entry->fileid = NFS_खाताID(inode);
			__entry->dev = inode->i_sb->s_dev;
			__entry->offset = data->args.offset;
			__entry->count = data->args.count;
			__assign_str(dstaddr, data->ds_clp ?
				rpc_peeraddr2str(data->ds_clp->cl_rpcclient,
					RPC_DISPLAY_ADDR) : "unknown");
		),

		TP_prपूर्णांकk(
			"error=%ld (%s) fileid=%02x:%02x:%llu fhandle=0x%08x "
			"offset=%llu count=%u dstaddr=%s",
			-__entry->error,
			show_nfsv4_errors(__entry->error),
			MAJOR(__entry->dev), MINOR(__entry->dev),
			(अचिन्हित दीर्घ दीर्घ)__entry->fileid,
			__entry->fhandle,
			__entry->offset, __entry->count,
			__get_str(dstaddr)
		)
);


#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

#पूर्ण_अगर /* _TRACE_NFS4_H */

#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#घोषणा TRACE_INCLUDE_खाता nfs4trace
/* This part must be outside protection */
#समावेश <trace/define_trace.h>
