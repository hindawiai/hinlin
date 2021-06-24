<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_NFSD_VFS_H
#घोषणा LINUX_NFSD_VFS_H

#समावेश "nfsfh.h"
#समावेश "nfsd.h"

/*
 * Flags क्रम nfsd_permission
 */
#घोषणा NFSD_MAY_NOP			0
#घोषणा NFSD_MAY_EXEC			0x001 /* == MAY_EXEC */
#घोषणा NFSD_MAY_WRITE			0x002 /* == MAY_WRITE */
#घोषणा NFSD_MAY_READ			0x004 /* == MAY_READ */
#घोषणा NFSD_MAY_SATTR			0x008
#घोषणा NFSD_MAY_TRUNC			0x010
#घोषणा NFSD_MAY_LOCK			0x020
#घोषणा NFSD_MAY_MASK			0x03f

/* extra hपूर्णांकs to permission and खोलो routines: */
#घोषणा NFSD_MAY_OWNER_OVERRIDE		0x040
#घोषणा NFSD_MAY_LOCAL_ACCESS		0x080 /* क्रम device special files */
#घोषणा NFSD_MAY_BYPASS_GSS_ON_ROOT	0x100
#घोषणा NFSD_MAY_NOT_BREAK_LEASE	0x200
#घोषणा NFSD_MAY_BYPASS_GSS		0x400
#घोषणा NFSD_MAY_READ_IF_EXEC		0x800

#घोषणा NFSD_MAY_64BIT_COOKIE		0x1000 /* 64 bit सूची_पढ़ो cookies क्रम >= NFSv3 */

#घोषणा NFSD_MAY_CREATE		(NFSD_MAY_EXEC|NFSD_MAY_WRITE)
#घोषणा NFSD_MAY_REMOVE		(NFSD_MAY_EXEC|NFSD_MAY_WRITE|NFSD_MAY_TRUNC)

काष्ठा nfsd_file;

/*
 * Callback function क्रम सूची_पढ़ो
 */
प्रकार पूर्णांक (*nfsd_filldir_t)(व्योम *, स्थिर अक्षर *, पूर्णांक, loff_t, u64, अचिन्हित);

/* nfsd/vfs.c */
पूर्णांक		nfsd_cross_mnt(काष्ठा svc_rqst *rqstp, काष्ठा dentry **dpp,
		                काष्ठा svc_export **expp);
__be32		nfsd_lookup(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				स्थिर अक्षर *, अचिन्हित पूर्णांक, काष्ठा svc_fh *);
__be32		 nfsd_lookup_dentry(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				स्थिर अक्षर *, अचिन्हित पूर्णांक,
				काष्ठा svc_export **, काष्ठा dentry **);
__be32		nfsd_setattr(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				काष्ठा iattr *, पूर्णांक, समय64_t);
पूर्णांक nfsd_mountpoपूर्णांक(काष्ठा dentry *, काष्ठा svc_export *);
#अगर_घोषित CONFIG_NFSD_V4
__be32          nfsd4_set_nfs4_label(काष्ठा svc_rqst *, काष्ठा svc_fh *,
		    काष्ठा xdr_netobj *);
__be32		nfsd4_vfs_fallocate(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				    काष्ठा file *, loff_t, loff_t, पूर्णांक);
__be32		nfsd4_clone_file_range(काष्ठा nfsd_file *nf_src, u64 src_pos,
				       काष्ठा nfsd_file *nf_dst, u64 dst_pos,
				       u64 count, bool sync);
#पूर्ण_अगर /* CONFIG_NFSD_V4 */
__be32		nfsd_create_locked(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *name, पूर्णांक len, काष्ठा iattr *attrs,
				पूर्णांक type, dev_t rdev, काष्ठा svc_fh *res);
__be32		nfsd_create(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *name, पूर्णांक len, काष्ठा iattr *attrs,
				पूर्णांक type, dev_t rdev, काष्ठा svc_fh *res);
#अगर_घोषित CONFIG_NFSD_V3
__be32		nfsd_access(काष्ठा svc_rqst *, काष्ठा svc_fh *, u32 *, u32 *);
__be32		करो_nfsd_create(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *name, पूर्णांक len, काष्ठा iattr *attrs,
				काष्ठा svc_fh *res, पूर्णांक createmode,
				u32 *verअगरier, bool *truncp, bool *created);
__be32		nfsd_commit(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				loff_t, अचिन्हित दीर्घ, __be32 *verf);
#पूर्ण_अगर /* CONFIG_NFSD_V3 */
#अगर_घोषित CONFIG_NFSD_V4
__be32		nfsd_getxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			    अक्षर *name, व्योम **bufp, पूर्णांक *lenp);
__be32		nfsd_listxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			    अक्षर **bufp, पूर्णांक *lenp);
__be32		nfsd_हटाओxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			    अक्षर *name);
__be32		nfsd_setxattr(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
			    अक्षर *name, व्योम *buf, u32 len, u32 flags);
#पूर्ण_अगर
पूर्णांक 		nfsd_खोलो_अवरोध_lease(काष्ठा inode *, पूर्णांक);
__be32		nfsd_खोलो(काष्ठा svc_rqst *, काष्ठा svc_fh *, umode_t,
				पूर्णांक, काष्ठा file **);
__be32		nfsd_खोलो_verअगरied(काष्ठा svc_rqst *, काष्ठा svc_fh *, umode_t,
				पूर्णांक, काष्ठा file **);
__be32		nfsd_splice_पढ़ो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
				काष्ठा file *file, loff_t offset,
				अचिन्हित दीर्घ *count,
				u32 *eof);
__be32		nfsd_पढ़ोv(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
				काष्ठा file *file, loff_t offset,
				काष्ठा kvec *vec, पूर्णांक vlen,
				अचिन्हित दीर्घ *count,
				u32 *eof);
__be32 		nfsd_पढ़ो(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				loff_t, काष्ठा kvec *, पूर्णांक, अचिन्हित दीर्घ *,
				u32 *eof);
__be32 		nfsd_ग_लिखो(काष्ठा svc_rqst *, काष्ठा svc_fh *, loff_t,
				काष्ठा kvec *, पूर्णांक, अचिन्हित दीर्घ *,
				पूर्णांक stable, __be32 *verf);
__be32		nfsd_vfs_ग_लिखो(काष्ठा svc_rqst *rqstp, काष्ठा svc_fh *fhp,
				काष्ठा nfsd_file *nf, loff_t offset,
				काष्ठा kvec *vec, पूर्णांक vlen, अचिन्हित दीर्घ *cnt,
				पूर्णांक stable, __be32 *verf);
__be32		nfsd_पढ़ोlink(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *, पूर्णांक *);
__be32		nfsd_symlink(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *name, पूर्णांक len, अक्षर *path,
				काष्ठा svc_fh *res);
__be32		nfsd_link(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				अक्षर *, पूर्णांक, काष्ठा svc_fh *);
sमाप_प्रकार		nfsd_copy_file_range(काष्ठा file *, u64,
				     काष्ठा file *, u64, u64);
__be32		nfsd_नाम(काष्ठा svc_rqst *,
				काष्ठा svc_fh *, अक्षर *, पूर्णांक,
				काष्ठा svc_fh *, अक्षर *, पूर्णांक);
__be32		nfsd_unlink(काष्ठा svc_rqst *, काष्ठा svc_fh *, पूर्णांक type,
				अक्षर *name, पूर्णांक len);
__be32		nfsd_सूची_पढ़ो(काष्ठा svc_rqst *, काष्ठा svc_fh *,
			     loff_t *, काष्ठा सूची_पढ़ो_cd *, nfsd_filldir_t);
__be32		nfsd_statfs(काष्ठा svc_rqst *, काष्ठा svc_fh *,
				काष्ठा kstatfs *, पूर्णांक access);

__be32		nfsd_permission(काष्ठा svc_rqst *, काष्ठा svc_export *,
				काष्ठा dentry *, पूर्णांक);

अटल अंतरभूत पूर्णांक fh_want_ग_लिखो(काष्ठा svc_fh *fh)
अणु
	पूर्णांक ret;

	अगर (fh->fh_want_ग_लिखो)
		वापस 0;
	ret = mnt_want_ग_लिखो(fh->fh_export->ex_path.mnt);
	अगर (!ret)
		fh->fh_want_ग_लिखो = true;
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम fh_drop_ग_लिखो(काष्ठा svc_fh *fh)
अणु
	अगर (fh->fh_want_ग_लिखो) अणु
		fh->fh_want_ग_लिखो = false;
		mnt_drop_ग_लिखो(fh->fh_export->ex_path.mnt);
	पूर्ण
पूर्ण

अटल अंतरभूत __be32 fh_getattr(स्थिर काष्ठा svc_fh *fh, काष्ठा kstat *stat)
अणु
	काष्ठा path p = अणु.mnt = fh->fh_export->ex_path.mnt,
			 .dentry = fh->fh_dentryपूर्ण;
	वापस nfsत्रुटि_सं(vfs_getattr(&p, stat, STATX_BASIC_STATS,
				    AT_STATX_SYNC_AS_STAT));
पूर्ण

अटल अंतरभूत पूर्णांक nfsd_create_is_exclusive(पूर्णांक createmode)
अणु
	वापस createmode == NFS3_CREATE_EXCLUSIVE
	       || createmode == NFS4_CREATE_EXCLUSIVE4_1;
पूर्ण

#पूर्ण_अगर /* LINUX_NFSD_VFS_H */
