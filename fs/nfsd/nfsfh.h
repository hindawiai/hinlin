<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 1995, 1996, 1997 Olaf Kirch <okir@monad.swb.de>
 *
 * This file describes the layout of the file handles as passed
 * over the wire.
 */
#अगर_अघोषित _LINUX_NFSD_NFSFH_H
#घोषणा _LINUX_NFSD_NFSFH_H

#समावेश <linux/crc32.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <uapi/linux/nfsd/nfsfh.h>
#समावेश <linux/iversion.h>
#समावेश <linux/exportfs.h>

अटल अंतरभूत __u32 ino_t_to_u32(ino_t ino)
अणु
	वापस (__u32) ino;
पूर्ण

अटल अंतरभूत ino_t u32_to_ino_t(__u32 uino)
अणु
	वापस (ino_t) uino;
पूर्ण

/*
 * This is the पूर्णांकernal representation of an NFS handle used in knfsd.
 * pre_mसमय/post_version will be used to support wcc_attr's in NFSv3.
 */
प्रकार काष्ठा svc_fh अणु
	काष्ठा knfsd_fh		fh_handle;	/* FH data */
	पूर्णांक			fh_maxsize;	/* max size क्रम fh_handle */
	काष्ठा dentry *		fh_dentry;	/* validated dentry */
	काष्ठा svc_export *	fh_export;	/* export poपूर्णांकer */

	bool			fh_locked;	/* inode locked by us */
	bool			fh_want_ग_लिखो;	/* remount protection taken */
	bool			fh_no_wcc;	/* no wcc data needed */
	bool			fh_no_atomic_attr;
						/*
						 * wcc data is not atomic with
						 * operation
						 */
	पूर्णांक			fh_flags;	/* FH flags */
#अगर_घोषित CONFIG_NFSD_V3
	bool			fh_post_saved;	/* post-op attrs saved */
	bool			fh_pre_saved;	/* pre-op attrs saved */

	/* Pre-op attributes saved during fh_lock */
	__u64			fh_pre_size;	/* size beक्रमe operation */
	काष्ठा बारpec64	fh_pre_mसमय;	/* mसमय beक्रमe oper */
	काष्ठा बारpec64	fh_pre_स_समय;	/* स_समय beक्रमe oper */
	/*
	 * pre-op nfsv4 change attr: note must check IS_I_VERSION(inode)
	 *  to find out अगर it is valid.
	 */
	u64			fh_pre_change;

	/* Post-op attributes saved in fh_unlock */
	काष्ठा kstat		fh_post_attr;	/* full attrs after operation */
	u64			fh_post_change; /* nfsv4 change; see above */
#पूर्ण_अगर /* CONFIG_NFSD_V3 */
पूर्ण svc_fh;
#घोषणा NFSD4_FH_FOREIGN (1<<0)
#घोषणा SET_FH_FLAG(c, f) ((c)->fh_flags |= (f))
#घोषणा HAS_FH_FLAG(c, f) ((c)->fh_flags & (f))

क्रमागत nfsd_fsid अणु
	FSID_DEV = 0,
	FSID_NUM,
	FSID_MAJOR_MINOR,
	FSID_ENCODE_DEV,
	FSID_UUID4_INUM,
	FSID_UUID8,
	FSID_UUID16,
	FSID_UUID16_INUM,
पूर्ण;

क्रमागत fsid_source अणु
	FSIDSOURCE_DEV,
	FSIDSOURCE_FSID,
	FSIDSOURCE_UUID,
पूर्ण;
बाह्य क्रमागत fsid_source fsid_source(स्थिर काष्ठा svc_fh *fhp);


/*
 * This might look a little large to "inline" but in all calls except
 * one, 'vers' is स्थिरant so moste of the function disappears.
 *
 * In some हालs the values are considered to be host endian and in
 * others, net endian. fsidv is always considered to be u32 as the
 * callers करोn't know which it will be. So we must use __क्रमce to keep
 * sparse from complaining. Since these values are opaque to the
 * client, that shouldn't be a problem.
 */
अटल अंतरभूत व्योम mk_fsid(पूर्णांक vers, u32 *fsidv, dev_t dev, ino_t ino,
			   u32 fsid, अचिन्हित अक्षर *uuid)
अणु
	u32 *up;
	चयन(vers) अणु
	हाल FSID_DEV:
		fsidv[0] = (__क्रमce __u32)htonl((MAJOR(dev)<<16) |
				 MINOR(dev));
		fsidv[1] = ino_t_to_u32(ino);
		अवरोध;
	हाल FSID_NUM:
		fsidv[0] = fsid;
		अवरोध;
	हाल FSID_MAJOR_MINOR:
		fsidv[0] = (__क्रमce __u32)htonl(MAJOR(dev));
		fsidv[1] = (__क्रमce __u32)htonl(MINOR(dev));
		fsidv[2] = ino_t_to_u32(ino);
		अवरोध;

	हाल FSID_ENCODE_DEV:
		fsidv[0] = new_encode_dev(dev);
		fsidv[1] = ino_t_to_u32(ino);
		अवरोध;

	हाल FSID_UUID4_INUM:
		/* 4 byte fsid and inode number */
		up = (u32*)uuid;
		fsidv[0] = ino_t_to_u32(ino);
		fsidv[1] = up[0] ^ up[1] ^ up[2] ^ up[3];
		अवरोध;

	हाल FSID_UUID8:
		/* 8 byte fsid  */
		up = (u32*)uuid;
		fsidv[0] = up[0] ^ up[2];
		fsidv[1] = up[1] ^ up[3];
		अवरोध;

	हाल FSID_UUID16:
		/* 16 byte fsid - NFSv3+ only */
		स_नकल(fsidv, uuid, 16);
		अवरोध;

	हाल FSID_UUID16_INUM:
		/* 8 byte inode and 16 byte fsid */
		*(u64*)fsidv = (u64)ino;
		स_नकल(fsidv+2, uuid, 16);
		अवरोध;
	शेष: BUG();
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक key_len(पूर्णांक type)
अणु
	चयन(type) अणु
	हाल FSID_DEV:		वापस 8;
	हाल FSID_NUM: 		वापस 4;
	हाल FSID_MAJOR_MINOR:	वापस 12;
	हाल FSID_ENCODE_DEV:	वापस 8;
	हाल FSID_UUID4_INUM:	वापस 8;
	हाल FSID_UUID8:	वापस 8;
	हाल FSID_UUID16:	वापस 16;
	हाल FSID_UUID16_INUM:	वापस 24;
	शेष: वापस 0;
	पूर्ण
पूर्ण

/*
 * Shorthand क्रम dprपूर्णांकk()'s
 */
बाह्य अक्षर * SVCFH_fmt(काष्ठा svc_fh *fhp);

/*
 * Function prototypes
 */
__be32	fh_verअगरy(काष्ठा svc_rqst *, काष्ठा svc_fh *, umode_t, पूर्णांक);
__be32	fh_compose(काष्ठा svc_fh *, काष्ठा svc_export *, काष्ठा dentry *, काष्ठा svc_fh *);
__be32	fh_update(काष्ठा svc_fh *);
व्योम	fh_put(काष्ठा svc_fh *);

अटल __अंतरभूत__ काष्ठा svc_fh *
fh_copy(काष्ठा svc_fh *dst, काष्ठा svc_fh *src)
अणु
	WARN_ON(src->fh_dentry || src->fh_locked);
			
	*dst = *src;
	वापस dst;
पूर्ण

अटल अंतरभूत व्योम
fh_copy_shallow(काष्ठा knfsd_fh *dst, काष्ठा knfsd_fh *src)
अणु
	dst->fh_size = src->fh_size;
	स_नकल(&dst->fh_base, &src->fh_base, src->fh_size);
पूर्ण

अटल __अंतरभूत__ काष्ठा svc_fh *
fh_init(काष्ठा svc_fh *fhp, पूर्णांक maxsize)
अणु
	स_रखो(fhp, 0, माप(*fhp));
	fhp->fh_maxsize = maxsize;
	वापस fhp;
पूर्ण

अटल अंतरभूत bool fh_match(काष्ठा knfsd_fh *fh1, काष्ठा knfsd_fh *fh2)
अणु
	अगर (fh1->fh_size != fh2->fh_size)
		वापस false;
	अगर (स_भेद(fh1->fh_base.fh_pad, fh2->fh_base.fh_pad, fh1->fh_size) != 0)
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool fh_fsid_match(काष्ठा knfsd_fh *fh1, काष्ठा knfsd_fh *fh2)
अणु
	अगर (fh1->fh_fsid_type != fh2->fh_fsid_type)
		वापस false;
	अगर (स_भेद(fh1->fh_fsid, fh2->fh_fsid, key_len(fh1->fh_fsid_type)) != 0)
		वापस false;
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_CRC32
/**
 * knfsd_fh_hash - calculate the crc32 hash क्रम the filehandle
 * @fh - poपूर्णांकer to filehandle
 *
 * वापसs a crc32 hash क्रम the filehandle that is compatible with
 * the one displayed by "wireshark".
 */

अटल अंतरभूत u32
knfsd_fh_hash(काष्ठा knfsd_fh *fh)
अणु
	वापस ~crc32_le(0xFFFFFFFF, (अचिन्हित अक्षर *)&fh->fh_base, fh->fh_size);
पूर्ण
#अन्यथा
अटल अंतरभूत u32
knfsd_fh_hash(काष्ठा knfsd_fh *fh)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_NFSD_V3
/*
 * The wcc data stored in current_fh should be cleared
 * between compound ops.
 */
अटल अंतरभूत व्योम
fh_clear_wcc(काष्ठा svc_fh *fhp)
अणु
	fhp->fh_post_saved = false;
	fhp->fh_pre_saved = false;
पूर्ण

/*
 * We could use i_version alone as the change attribute.  However,
 * i_version can go backwards after a reboot.  On its own that करोesn't
 * necessarily cause a problem, but अगर i_version goes backwards and then
 * is incremented again it could reuse a value that was previously used
 * beक्रमe boot, and a client who queried the two values might
 * incorrectly assume nothing changed.
 *
 * By using both स_समय and the i_version counter we guarantee that as
 * दीर्घ as समय करोesn't go backwards we never reuse an old value.
 */
अटल अंतरभूत u64 nfsd4_change_attribute(काष्ठा kstat *stat,
					 काष्ठा inode *inode)
अणु
	अगर (inode->i_sb->s_export_op->fetch_iversion)
		वापस inode->i_sb->s_export_op->fetch_iversion(inode);
	अन्यथा अगर (IS_I_VERSION(inode)) अणु
		u64 chattr;

		chattr =  stat->स_समय.tv_sec;
		chattr <<= 30;
		chattr += stat->स_समय.tv_nsec;
		chattr += inode_query_iversion(inode);
		वापस chattr;
	पूर्ण अन्यथा
		वापस समय_प्रकारo_chattr(&stat->स_समय);
पूर्ण

बाह्य व्योम fill_pre_wcc(काष्ठा svc_fh *fhp);
बाह्य व्योम fill_post_wcc(काष्ठा svc_fh *fhp);
#अन्यथा
#घोषणा fh_clear_wcc(ignored)
#घोषणा fill_pre_wcc(ignored)
#घोषणा fill_post_wcc(notused)
#पूर्ण_अगर /* CONFIG_NFSD_V3 */


/*
 * Lock a file handle/inode
 * NOTE: both fh_lock and fh_unlock are करोne "by hand" in
 * vfs.c:nfsd_नाम as it needs to grab 2 i_mutex's at once
 * so, any changes here should be reflected there.
 */

अटल अंतरभूत व्योम
fh_lock_nested(काष्ठा svc_fh *fhp, अचिन्हित पूर्णांक subclass)
अणु
	काष्ठा dentry	*dentry = fhp->fh_dentry;
	काष्ठा inode	*inode;

	BUG_ON(!dentry);

	अगर (fhp->fh_locked) अणु
		prपूर्णांकk(KERN_WARNING "fh_lock: %pd2 already locked!\n",
			dentry);
		वापस;
	पूर्ण

	inode = d_inode(dentry);
	inode_lock_nested(inode, subclass);
	fill_pre_wcc(fhp);
	fhp->fh_locked = true;
पूर्ण

अटल अंतरभूत व्योम
fh_lock(काष्ठा svc_fh *fhp)
अणु
	fh_lock_nested(fhp, I_MUTEX_NORMAL);
पूर्ण

/*
 * Unlock a file handle/inode
 */
अटल अंतरभूत व्योम
fh_unlock(काष्ठा svc_fh *fhp)
अणु
	अगर (fhp->fh_locked) अणु
		fill_post_wcc(fhp);
		inode_unlock(d_inode(fhp->fh_dentry));
		fhp->fh_locked = false;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* _LINUX_NFSD_NFSFH_H */
