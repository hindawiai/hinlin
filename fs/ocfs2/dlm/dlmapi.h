<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * dlmapi.h
 *
 * बाह्यally exported dlm पूर्णांकerfaces
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित DLMAPI_H
#घोषणा DLMAPI_H

काष्ठा dlm_lock;
काष्ठा dlm_ctxt;

/* NOTE: changes made to this क्रमागत should be reflected in dlmdebug.c */
क्रमागत dlm_status अणु
	DLM_NORMAL = 0,           /*  0: request in progress */
	DLM_GRANTED,              /*  1: request granted */
	DLM_DENIED,               /*  2: request denied */
	DLM_DENIED_NOLOCKS,       /*  3: request denied, out of प्रणाली resources */
	DLM_WORKING,              /*  4: async request in progress */
	DLM_BLOCKED,              /*  5: lock request blocked */
	DLM_BLOCKED_ORPHAN,       /*  6: lock request blocked by a orphan lock*/
	DLM_DENIED_GRACE_PERIOD,  /*  7: topological change in progress */
	DLM_SYSERR,               /*  8: प्रणाली error */
	DLM_NOSUPPORT,            /*  9: unsupported */
	DLM_CANCELGRANT,          /* 10: can't cancel convert: alपढ़ोy granted */
	DLM_IVLOCKID,             /* 11: bad lockid */
	DLM_SYNC,                 /* 12: synchronous request granted */
	DLM_BADTYPE,              /* 13: bad resource type */
	DLM_BADRESOURCE,          /* 14: bad resource handle */
	DLM_MAXHANDLES,           /* 15: no more resource handles */
	DLM_NOCLINFO,             /* 16: can't contact cluster manager */
	DLM_NOLOCKMGR,            /* 17: can't contact lock manager */
	DLM_NOPURGED,             /* 18: can't contact purge daemon */
	DLM_BADARGS,              /* 19: bad api args */
	DLM_VOID,                 /* 20: no status */
	DLM_NOTQUEUED,            /* 21: NOQUEUE was specअगरied and request failed */
	DLM_IVBUFLEN,             /* 22: invalid resource name length */
	DLM_CVTUNGRANT,           /* 23: attempted to convert ungranted lock */
	DLM_BADPARAM,             /* 24: invalid lock mode specअगरied */
	DLM_VALNOTVALID,          /* 25: value block has been invalidated */
	DLM_REJECTED,             /* 26: request rejected, unrecognized client */
	DLM_ABORT,                /* 27: blocked lock request cancelled */
	DLM_CANCEL,               /* 28: conversion request cancelled */
	DLM_IVRESHANDLE,          /* 29: invalid resource handle */
	DLM_DEADLOCK,             /* 30: deadlock recovery refused this request */
	DLM_DENIED_NOASTS,        /* 31: failed to allocate AST */
	DLM_FORWARD,              /* 32: request must रुको क्रम primary's response */
	DLM_TIMEOUT,              /* 33: समयout value क्रम lock has expired */
	DLM_IVGROUPID,            /* 34: invalid group specअगरication */
	DLM_VERS_CONFLICT,        /* 35: version conflicts prevent request handling */
	DLM_BAD_DEVICE_PATH,      /* 36: Locks device करोes not exist or path wrong */
	DLM_NO_DEVICE_PERMISSION, /* 37: Client has insufficient pers क्रम device */
	DLM_NO_CONTROL_DEVICE,    /* 38: Cannot set options on खोलोed device */

	DLM_RECOVERING,           /* 39: extension, allows caller to fail a lock
				     request अगर it is being recovered */
	DLM_MIGRATING,            /* 40: extension, allows caller to fail a lock
				     request अगर it is being migrated */
	DLM_MAXSTATS,             /* 41: upper limit क्रम वापस code validation */
पूर्ण;

/* क्रम pretty-prपूर्णांकing dlm_status error messages */
स्थिर अक्षर *dlm_errmsg(क्रमागत dlm_status err);
/* क्रम pretty-prपूर्णांकing dlm_status error names */
स्थिर अक्षर *dlm_errname(क्रमागत dlm_status err);

/* Eventually the DLM will use standard त्रुटि_सं values, but in the
 * meanसमय this lets us track dlm errors as they bubble up. When we
 * bring its error reporting पूर्णांकo line with the rest of the stack,
 * these can just be replaced with calls to mlog_त्रुटि_सं. */
#घोषणा dlm_error(st) करो अणु						\
	अगर ((st) != DLM_RECOVERING &&					\
	    (st) != DLM_MIGRATING &&					\
	    (st) != DLM_FORWARD)					\
		mlog(ML_ERROR, "dlm status = %s\n", dlm_errname((st)));	\
पूर्ण जबतक (0)

#घोषणा DLM_LKSB_UNUSED1           0x01
#घोषणा DLM_LKSB_PUT_LVB           0x02
#घोषणा DLM_LKSB_GET_LVB           0x04
#घोषणा DLM_LKSB_UNUSED2           0x08
#घोषणा DLM_LKSB_UNUSED3           0x10
#घोषणा DLM_LKSB_UNUSED4           0x20
#घोषणा DLM_LKSB_UNUSED5           0x40
#घोषणा DLM_LKSB_UNUSED6           0x80

#घोषणा DLM_LVB_LEN  64

/* Callers are only allowed access to the lvb and status members of
 * this काष्ठा. */
काष्ठा dlm_lockstatus अणु
	क्रमागत dlm_status status;
	u32 flags;
	काष्ठा dlm_lock *lockid;
	अक्षर lvb[DLM_LVB_LEN];
पूर्ण;

/* Valid lock modes. */
#घोषणा LKM_IVMODE      (-1)            /* invalid mode */
#घोषणा LKM_NLMODE      0               /* null lock */
#घोषणा LKM_CRMODE      1               /* concurrent पढ़ो    unsupported */
#घोषणा LKM_CWMODE      2               /* concurrent ग_लिखो   unsupported */
#घोषणा LKM_PRMODE      3               /* रक्षित पढ़ो */
#घोषणा LKM_PWMODE      4               /* रक्षित ग_लिखो    unsupported */
#घोषणा LKM_EXMODE      5               /* exclusive */
#घोषणा LKM_MAXMODE     5
#घोषणा LKM_MODEMASK    0xff

/* Flags passed to dlmlock and dlmunlock:
 * reserved: flags used by the "real" dlm
 * only a few are supported by this dlm
 * (U) = unsupported by ocfs2 dlm */
#घोषणा LKM_ORPHAN       0x00000010  /* this lock is orphanable (U) */
#घोषणा LKM_PARENTABLE   0x00000020  /* this lock was orphaned (U) */
#घोषणा LKM_BLOCK        0x00000040  /* blocking lock request (U) */
#घोषणा LKM_LOCAL        0x00000080  /* local lock request */
#घोषणा LKM_VALBLK       0x00000100  /* lock value block request */
#घोषणा LKM_NOQUEUE      0x00000200  /* non blocking request */
#घोषणा LKM_CONVERT      0x00000400  /* conversion request */
#घोषणा LKM_NODLCKWT     0x00000800  /* this lock wont deadlock (U) */
#घोषणा LKM_UNLOCK       0x00001000  /* deallocate this lock */
#घोषणा LKM_CANCEL       0x00002000  /* cancel conversion request */
#घोषणा LKM_DEQALL       0x00004000  /* हटाओ all locks held by proc (U) */
#घोषणा LKM_INVVALBLK    0x00008000  /* invalidate lock value block */
#घोषणा LKM_SYNCSTS      0x00010000  /* वापस synchronous status अगर poss (U) */
#घोषणा LKM_TIMEOUT      0x00020000  /* lock request contains समयout (U) */
#घोषणा LKM_SNGLDLCK     0x00040000  /* request can self-deadlock (U) */
#घोषणा LKM_FINDLOCAL    0x00080000  /* find local lock request (U) */
#घोषणा LKM_PROC_OWNED   0x00100000  /* owned by process, not group (U) */
#घोषणा LKM_XID          0x00200000  /* use transaction id क्रम deadlock (U) */
#घोषणा LKM_XID_CONFLICT 0x00400000  /* करो not allow lock inheritance (U) */
#घोषणा LKM_FORCE        0x00800000  /* क्रमce unlock flag */
#घोषणा LKM_REVVALBLK    0x01000000  /* temporary solution: re-validate
					lock value block (U) */
/* unused */
#घोषणा LKM_UNUSED1      0x00000001  /* unused */
#घोषणा LKM_UNUSED2      0x00000002  /* unused */
#घोषणा LKM_UNUSED3      0x00000004  /* unused */
#घोषणा LKM_UNUSED4      0x00000008  /* unused */
#घोषणा LKM_UNUSED5      0x02000000  /* unused */
#घोषणा LKM_UNUSED6      0x04000000  /* unused */
#घोषणा LKM_UNUSED7      0x08000000  /* unused */

/* ocfs2 extensions: पूर्णांकernal only
 * should never be used by caller */
#घोषणा LKM_MIGRATION    0x10000000  /* extension: lockres is to be migrated
					to another node */
#घोषणा LKM_PUT_LVB      0x20000000  /* extension: lvb is being passed
					should be applied to lockres */
#घोषणा LKM_GET_LVB      0x40000000  /* extension: lvb should be copied
					from lockres when lock is granted */
#घोषणा LKM_RECOVERY     0x80000000  /* extension: flag क्रम recovery lock
					used to aव्योम recovery rwsem */


प्रकार व्योम (dlm_astlockfunc_t)(व्योम *);
प्रकार व्योम (dlm_bastlockfunc_t)(व्योम *, पूर्णांक);
प्रकार व्योम (dlm_astunlockfunc_t)(व्योम *, क्रमागत dlm_status);

क्रमागत dlm_status dlmlock(काष्ठा dlm_ctxt *dlm,
			पूर्णांक mode,
			काष्ठा dlm_lockstatus *lksb,
			पूर्णांक flags,
			स्थिर अक्षर *name,
			पूर्णांक namelen,
			dlm_astlockfunc_t *ast,
			व्योम *data,
			dlm_bastlockfunc_t *bast);

क्रमागत dlm_status dlmunlock(काष्ठा dlm_ctxt *dlm,
			  काष्ठा dlm_lockstatus *lksb,
			  पूर्णांक flags,
			  dlm_astunlockfunc_t *unlockast,
			  व्योम *data);

काष्ठा dlm_protocol_version अणु
	u8 pv_major;
	u8 pv_minor;
पूर्ण;
काष्ठा dlm_ctxt * dlm_रेजिस्टर_करोमुख्य(स्थिर अक्षर *करोमुख्य, u32 key,
				      काष्ठा dlm_protocol_version *fs_proto);

व्योम dlm_unरेजिस्टर_करोमुख्य(काष्ठा dlm_ctxt *dlm);

व्योम dlm_prपूर्णांक_one_lock(काष्ठा dlm_lock *lockid);

प्रकार व्योम (dlm_eviction_func)(पूर्णांक, व्योम *);
काष्ठा dlm_eviction_cb अणु
	काष्ठा list_head        ec_item;
	dlm_eviction_func       *ec_func;
	व्योम                    *ec_data;
पूर्ण;
व्योम dlm_setup_eviction_cb(काष्ठा dlm_eviction_cb *cb,
			   dlm_eviction_func *f,
			   व्योम *data);
व्योम dlm_रेजिस्टर_eviction_cb(काष्ठा dlm_ctxt *dlm,
			      काष्ठा dlm_eviction_cb *cb);
व्योम dlm_unरेजिस्टर_eviction_cb(काष्ठा dlm_eviction_cb *cb);

#पूर्ण_अगर /* DLMAPI_H */
